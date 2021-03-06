#ifndef __kvlAtlasMeshMultiAlphaDrawer_h
#define __kvlAtlasMeshMultiAlphaDrawer_h

#include "kvlAtlasMeshRasterizor.h"


namespace kvl
{


namespace FragmentProcessor 
{

/**
 *
 */
class DrawMultiAlpha
{
public:
  
  typedef itk::Image< AtlasAlphasType, 3 >  ImageType;

  DrawMultiAlpha() 
    {
    m_Image = 0;
    m_AlphasInVertex0 = 0;
    m_AlphasInVertex1 = 0;
    m_AlphasInVertex2 = 0;
    m_AlphasInVertex3 = 0;
    m_Mesh = 0;
    }

  ~DrawMultiAlpha() {};

  void AllocateImage( ImageType::SizeType  size )
    {
    m_Image = ImageType::New();
    m_Image->SetRegions( size );
    m_Image->Allocate();
    }

  void SetImage( ImageType* image )
    {
    m_Image = image;
    }
    
  const ImageType* GetImage() const
    { return m_Image; }

  ImageType* GetImage()
    { return m_Image; }
  
  inline void operator()( const float& pi0, const float& pi1, const float& pi2, const float& pi3 )
    {
    AtlasAlphasType&  alphas = m_Image->GetPixel( m_Index );
    for ( unsigned int classNumber = 0; classNumber < m_AlphasInVertex0->Size(); classNumber++ )
      {
      alphas[ classNumber ] = pi0 * ( ( *m_AlphasInVertex0 )[ classNumber ] ) +
                              pi1 * ( ( *m_AlphasInVertex1 )[ classNumber ] ) +
                              pi2 * ( ( *m_AlphasInVertex2 )[ classNumber ] ) +
                              pi3 * ( ( *m_AlphasInVertex3 )[ classNumber ] );
      }
      
    m_Index[ 0 ]++;
    }
    
  inline void StartNewSpan( int x, int y, int z, const unsigned char* sourcePointer )
    {
    m_Index[ 0 ] = x;
    m_Index[ 1 ] = y;
    m_Index[ 2 ] = z;
#if 0
    if ( z == 49 )
      {
      std::cout << "         Starting span (" << x << ", " << y << ", " << z << ")" << std::endl;
      }
#endif
    }
    
  inline bool StartNewTetrahedron( AtlasMesh::CellIdentifier cellId )
    {
    // Cache the alpha of the specified class in each of the vertices of this tetrahedron
    AtlasMesh::CellAutoPointer  cell;
    m_Mesh->GetCell( cellId, cell );
          
    AtlasMesh::CellType::PointIdIterator  pit = cell->PointIdsBegin();

    m_AlphasInVertex0 = &( m_Mesh->GetPointData()->ElementAt( *pit ).m_Alphas );
    ++pit;
    m_AlphasInVertex1 = &( m_Mesh->GetPointData()->ElementAt( *pit ).m_Alphas );
    ++pit;
    m_AlphasInVertex2 = &( m_Mesh->GetPointData()->ElementAt( *pit ).m_Alphas );
    ++pit;
    m_AlphasInVertex3 = &( m_Mesh->GetPointData()->ElementAt( *pit ).m_Alphas );

    return true;
    }
    
  inline void SetMesh( const AtlasMesh* mesh )
    {
    m_Mesh = mesh;
    }
    
private:

  ImageType::Pointer  m_Image;
  ImageType::IndexType  m_Index;
  
  const AtlasAlphasType*  m_AlphasInVertex0;
  const AtlasAlphasType*  m_AlphasInVertex1;
  const AtlasAlphasType*  m_AlphasInVertex2;
  const AtlasAlphasType*  m_AlphasInVertex3;

  AtlasMesh::ConstPointer  m_Mesh;
  
    
};


} // End namespace FragmentProcessor


/**
 *
 */
class AtlasMeshMultiAlphaDrawer: public AtlasMeshRasterizor< FragmentProcessor::DrawMultiAlpha >
{
public :
  
  /** Standard class typedefs */
  typedef AtlasMeshMultiAlphaDrawer  Self;
  typedef AtlasMeshRasterizor< FragmentProcessor::DrawMultiAlpha >  Superclass;
  typedef itk::SmartPointer< Self >  Pointer;
  typedef itk::SmartPointer< const Self >  ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro( Self );

  /** Run-time type information (and related methods). */
  itkTypeMacro( AtlasMeshMultiAlphaDrawer, itk::Object );

  /** Some typedefs */
  typedef Superclass::FragmentProcessorType  FragmentProcessorType;
  typedef Superclass::LabelImageType  LabelImageType;
  typedef FragmentProcessorType::ImageType  AlphasImageType;

  /** */
  void SetAlphasImage( AlphasImageType* image )
    { 
    for ( std::vector< FragmentProcessorType >::iterator  it = this->GetFragmentProcessors().begin();
          it != this->GetFragmentProcessors().end(); ++it )
      {
      it->SetImage( image );
      }
    }

  /** */
  const AlphasImageType* GetAlphasImage() const
    { return this->GetFragmentProcessor().GetImage(); }

  /** */
  virtual void Rasterize( const AtlasMesh* mesh )
    {
    // Make sure we have an image to work on
    if ( !this->GetFragmentProcessor().GetImage() )
      {
      // Allocate the result image for the first fragment processor, and point to the other
      // fragment processors to that 
      std::vector< FragmentProcessorType >::iterator  it = this->GetFragmentProcessors().begin();  
      std::cout << "Allocating alphas image..." << std::flush;
      it->AllocateImage( this->GetLabelImage()->GetLargestPossibleRegion().GetSize() );
      std::cout << "done" << std::endl;
      AlphasImageType::Pointer  image = const_cast< AlphasImageType* >( it->GetImage() );
      for ( ; it != this->GetFragmentProcessors().end(); ++it )
        {
        it->SetImage( image );
        }
      }

    // Make sure the image is initialized with an array of the correct lenght in each voxel,
    // and has by default background everywhere
    AtlasAlphasType  defaultAlphas( mesh->GetPointData()->Begin().Value().m_Alphas.Size() );
    defaultAlphas.Fill( 0.0f );
    //defaultAlphas( 0 ) = 1.0f;
    this->GetFragmentProcessor().GetImage()->FillBuffer( defaultAlphas );

    // Invoke superclass' implementation using multi-threading
    Superclass::Rasterize( mesh, true );
    }

protected:
  AtlasMeshMultiAlphaDrawer() {};
  virtual ~AtlasMeshMultiAlphaDrawer() {};

private:
  AtlasMeshMultiAlphaDrawer(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented
  
  
};


} // end namespace kvl

#endif

