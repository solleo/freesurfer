
// STL
#include <fstream>
#include <iostream>
#include <list>

// BOOST
//#include <boost/filesystem/operations.hpp>
//#include <boost/filesystem/exception.hpp>

// OWN
#include "solver.h"
#include "pbmesh_crop.h"

#include "untangler.h"

// the following doesn't seem to be used anywhere and causes link errors in debug mode
#if 0
typedef std::list<unsigned int> ListType;

static void write_dbg_information( const CMesh3d& mesh,
                                   ListType& boundary,
                                   ListType& tetTangled)
{
  // delete tangle temp directory
  namespace bf = boost::filesystem;
  typedef TPbMeshCrop<Constructor,3> MeshCrop;
  try
  {
    bf::path tmp_dir("ttmp", bf::native);
    if ( bf::exists(tmp_dir) )
    {
      if (!bf::is_empty(tmp_dir))
        bf::remove_all(tmp_dir);
      else // dir is empty
        bf::remove(tmp_dir);
    }
  }
  catch (bf::filesystem_error& er)
  {
    std::cerr << " Filesystem error while trying to remove tmp dir : \n"
    << er.who() << std::endl;
  }
  // create tmp directory
  bf::path tmp_dir("ttmp", bf::native);
  bf::create_directory( tmp_dir );

  // now the actual write part
  std::ofstream ofs;

  //-----------------
  // write geometry
  ofs.open( ( tmp_dir / "0_geometry.txt" ).string().c_str() );
  if (!ofs)
  {
    std::cerr << " Failed creating geometry file\n";
    exit(1);
  }
  for (unsigned int ui(0), nnodes(mesh.get_no_nodes());
       ui<nnodes; ++ui)
  {
    MeshCrop::NodeType* pnode;
    mesh.get_node(ui, &pnode);
    ofs << pnode->coords() << std::endl;
  }
  ofs.close();

  //------------------
  // write delta
  ofs.open( ( tmp_dir / "0_delta.txt" ).string().c_str() );
  if (!ofs)
  {
    std::cerr << " Failed creating delta file\n";
    exit(1);
  }
  for (unsigned int ui(0), nnodes(mesh.get_no_nodes());
       ui<nnodes; ++ui)
  {
    MeshCrop::NodeType* pnode;
    mesh.get_node(ui, &pnode);
    ofs << pnode->delta() << std::endl;
  }
  ofs.close();

  //--------------------
  // connectivity
  ofs.open( (tmp_dir/"0_connectivity.txt").string().c_str() );
  if (!ofs)
  {
    std::cerr << " Failed creating connectivity file\n";
    exit(1);
  }
  for (unsigned int ui(0), nelts(mesh.get_no_elts());
       ui<nelts; ++ui)
  {
    const MeshCrop::ElementType* cpelt = mesh.get_elt(ui);
    for (unsigned int n(0), nnodes(cpelt->no_nodes());
         n<nnodes; ++n)
    {
      MeshCrop::NodeType* pnode;
      cpelt->get_node(n, &pnode);
      ofs << pnode->get_id() << (n<nnodes-1?" ":"");
    }
    ofs << std::endl;
  }

  //----------------------
  // write the indices of the elements with pbs
  ofs.open( (tmp_dir/"0_index.txt").string().c_str() );
  if (!ofs)
  {
    std::cerr << " Failed creating index file\n";
    exit(1);
  }
  for (ListType::const_iterator cit = tetTangled.begin();
       cit != tetTangled.end(); ++cit )
    ofs << *cit << " ";
  ofs << std::endl;
  ofs.close();

  //-----------------------
  // boundary file
  ofs.open( (tmp_dir/"0_boundary.txt").string().c_str() );
  if (!ofs)
  {
    std::cerr << " Failed creating boundary file\n";
    exit(1);
  }
  for (ListType::const_iterator cit = boundary.begin();
       cit != boundary.end(); ++cit )
    ofs << *cit << std::endl;
  ofs.close();
}
#endif

/*

at the end, if still topology problems, check they are not NEW ones

*/
#undef __FUNCT__
#define __FUNCT__ "solve_topology_problems"
void
solve_topology_problems( TMesh3d& mesh,
                         unsigned int neighborhood,
                         bool dbgMode )
{

  // typedefs
  //typedef CMesh3d::ElementIndexContainer EltIndexContainer;
  typedef TPbMeshCrop<Constructor,3> MeshCrop;
  typedef MeshCrop::MapType MapType;
  typedef MeshCrop::IndexSetType IndexSetType;
  typedef std::vector<unsigned int> VectorType;
  typedef TDirectSolver<Constructor, 3> SolverType;
  typedef VMaterial MaterialType;
  typedef CMesh3d::MaterialConstIteratorType MaterialConstIteratorType;
  typedef CMesh3d::tNode NodeType;

  // declarations
  VectorType vecContainer;
  std::insert_iterator<VectorType> ii(vecContainer, vecContainer.begin());
  // search for orientation problems in the destination (dst) frame
  try
  {
    mesh.orientation_pb( dst,ii );
  }
  catch ( const std::exception& e)
  {
    std::cout << " Exception caught while gathering info on topology problems\n"
    << e.what() << std::endl;
  }

  if ( vecContainer.empty() ) // no tangling in this mesh
    return;

  unsigned int noElts = vecContainer.size();
  std::sort( vecContainer.begin(), vecContainer.end() );
  VectorType vecPreContainer = vecContainer;

  MeshCrop crop(&mesh);
  MaterialConstIteratorType materialBegin, materialEnd;
  mesh.get_material_iterators(materialBegin, materialEnd);
  double de = materialBegin->second->get_E();
  double dnu = materialBegin->second->get_nu();
  std::cout << " using Lame constants given by " << std::endl
  << " E = " << de << std::endl
  << " nu = " << dnu << std::endl;

  NodeType *pnode = NULL;
  NodeType *pInitNode = NULL;
  /*
    in the following, problems are clustered and eliminated until nothing remains
    this is done because it makes sense to localize problems and use as boundary
    valid tetrahedra (since solving a local problem while keeping consistent with the
    global mesh is facilitated much by this assumption)

    one key element in the clustering algorithm is an efficient set difference operation.
    This is done using the std::set_difference algorithm, which requires sorted inputs.
    Hence I am forced to use std::sort, which requires random access iterators.
    Using random access iterators in turn makes using lists impossible.

    Future suggestion: when an algorithm needs a container populated, as is the case of
    orientation_pb, provide a templatized version which provides an INSERT ITERATOR.
  */
  while ( !vecContainer.empty() )
  {
    CMesh3d cropMesh;
    MapType nodeMap, elementMap;
    IndexSetType boundaryNodes;

    crop.Crop( &cropMesh,
               nodeMap,
               elementMap,
               boundaryNodes,
               vecContainer.front(),
               neighborhood
             );

    //------------------------------------
    //
    // equivalent to ++ in normal for loop
    //
    // remove problem nodes from the original container
    VectorType vecCrop;
    std::insert_iterator<VectorType> orientation_ii(vecCrop, vecCrop.begin());
    /*
    determine local problems
    eliminate them from the global container using the element map
    element_map [ local_index ] = global_index
    */
    cropMesh.orientation_pb( dst, orientation_ii );


    for (VectorType::iterator itIndex = vecCrop.begin();
         itIndex != vecCrop.end(); ++itIndex )
      *itIndex = elementMap[ *itIndex ];

    VectorType deltaContainer;
    std::insert_iterator<VectorType> cropii(deltaContainer, deltaContainer.begin() );
    std::set_difference( vecContainer.begin(), vecContainer.end(),
                         vecCrop.begin(), vecCrop.end(),
                         cropii );
    vecContainer = deltaContainer; // in view of future iterations
    //
    //----------------------------------------

    cropMesh.build_index_src();
    // set material to new mesh
    // copy from old mesh

    // if using the same material in 2 consecutive iterations, the material is destroyed
    // solution - use smart pointers for materials or take out that function from the interface.
    //cropMesh.set_default_material( pmaterial);
    cropMesh.set_constants( de, dnu );
    // solve the local problem
    SolverType solver;
    solver.set_mesh( &cropMesh );

    // add bc
    for ( IndexSetType::const_iterator cit = boundaryNodes.begin();
          cit != boundaryNodes.end(); ++cit )
    {
      cropMesh.get_node( *cit, &pnode );
      solver.add_bc_natural( pnode,
                             pnode->delta() );
    } // next cit
    std::cout << " solving cropped problem\n";
    solver.solve();

    // check for orientation problems
    if ( cropMesh.orientation_pb( dst ) )
      std::cout << " Still having pbs after untangling\n";


    // commit delta back to the original mesh
    VectorType::const_iterator findCit;
    bool btest = false;
    for (unsigned int ui(0), nnodes(cropMesh.get_no_nodes());
         ui < nnodes; ++ui)
    {
      cropMesh.get_node(ui, &pnode);
      mesh.get_node( nodeMap[ui], &pInitNode );

      if ( std::find(boundaryNodes.begin(),
                     boundaryNodes.end(),
                     ui ) != boundaryNodes.end() )
      {
        btest = true;
        // node is a boundary node - compare deltas
        if ( (pnode->delta() - pInitNode->delta()).norm() > 1.0e-5 )
        {
          std::cerr << " delta mismatch  init = " << pInitNode->delta()
          << " new = " << pnode->delta() << std::endl;
        }
      }

      pInitNode->set_delta( pnode->delta() );
    } // next ui
    std::cout << " btest = " << btest << std::endl;
  }

  // check no NEW orientation pbs appeared
  VectorType vecAfter;
  std::insert_iterator<VectorType> after_ii(vecAfter, vecAfter.begin());

  std::cout << " before \n";
  mesh.orientation_pb( dst, after_ii);
  std::cout << " after\n";
  if ( !vecAfter.empty() )
  {
    std::cout << " orientation pbs persisting\n"
    << " initially " << noElts << std::endl
    << " post = " << vecAfter.size() << std::endl;
    std::sort(vecAfter.begin(), vecAfter.end());

    VectorType deltaContainer;
    std::insert_iterator<VectorType>
    iiDelta(deltaContainer,deltaContainer.begin());
    std::set_difference( vecAfter.begin(), vecAfter.end(),
                         vecPreContainer.begin(), vecPreContainer.end(),
                         iiDelta );
    std::cout << " new problems size = " << deltaContainer.size()
    << std::endl;
  }
  else
    std::cout << " !!!! No residual problems.\n";

}


