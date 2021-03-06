/**
 * @file  ThreadIOWorker.cpp
 * @brief REPLACE_WITH_ONE_LINE_SHORT_DESCRIPTION
 *
 */
/*
 * Original Author: Ruopeng Wang
 * CVS Revision Info:
 *    $Author: rpwang $
 *    $Date: 2011/05/13 15:04:33 $
 *    $Revision: 1.4.2.3 $
 *
 * Copyright © 2011 The General Hospital Corporation (Boston, MA) "MGH"
 *
 * Terms and conditions for use, reproduction, distribution and contribution
 * are found in the 'FreeSurfer Software License Agreement' contained
 * in the file 'LICENSE' found in the FreeSurfer distribution, and here:
 *
 * https://surfer.nmr.mgh.harvard.edu/fswiki/FreeSurferSoftwareLicense
 *
 * Reporting: freesurfer@nmr.mgh.harvard.edu
 *
 */
#include "ThreadIOWorker.h"
#include "LayerMRI.h"
#include "LayerSurface.h"
#include "LayerDTI.h"
#include "LayerPLabel.h"
#include "LayerTrack.h"
#include "LayerVolumeTrack.h"

ThreadIOWorker::ThreadIOWorker(QObject *parent) :
  QThread(parent),
  m_nJobType( JT_LoadVolume ),
  m_layer( NULL )
{
}

void ThreadIOWorker::LoadVolume( Layer* layer, const QVariantMap& args )
{
  m_layer = layer;
  m_nJobType = JT_LoadVolume;
  m_args = args;
  start();
}

void ThreadIOWorker::SaveVolume( Layer* layer, const QVariantMap& args )
{
  m_layer = layer;
  m_nJobType = JT_SaveVolume;
  m_args = args;
  start();
}

void ThreadIOWorker::LoadSurface( Layer* layer, const QVariantMap& args )
{
  m_layer = layer;
  m_nJobType = JT_LoadSurface;
  m_args = args;
  start();
}

void ThreadIOWorker::LoadSurfaceOverlay( Layer* layer, const QVariantMap& args )
{
  m_layer = layer;
  m_nJobType = JT_LoadSurfaceOverlay;
  m_args = args;
  start();
}

void ThreadIOWorker::LoadTrack( Layer* layer, const QVariantMap& args)
{
  m_layer = layer;
  m_nJobType = JT_LoadTrack;
  m_args = args;
  start();
}

void ThreadIOWorker::run()
{
  if ( m_nJobType == JT_LoadVolume )
  {
    if (m_layer->IsTypeOf("DTI"))
    {
      LayerDTI* mri = qobject_cast<LayerDTI*>( m_layer );
      if ( !mri )
      {
        return;
      }
      if ( !mri->LoadDTIFromFile() )
      {
        emit Error( m_layer, m_nJobType );
      }
      else
      {
        emit Finished( m_layer, m_nJobType );
      }
    }
    else if (m_layer->IsTypeOf("PLabel"))
    {
      LayerPLabel* mri = qobject_cast<LayerPLabel*>( m_layer );
      if ( !mri )
      {
        return;
      }
      if ( !mri->LoadVolumeFiles() )
      {
        emit Error( m_layer, m_nJobType );
      }
      else
      {
        emit Finished( m_layer, m_nJobType );
      }
    }
    else if (m_layer->IsTypeOf("VolumeTrack"))
    {
      LayerVolumeTrack* mri = qobject_cast<LayerVolumeTrack*>( m_layer );
      if ( !mri )
      {
        return;
      }
      if ( !mri->LoadFromFile() )
      {
        emit Error( m_layer, m_nJobType );
      }
      else
      {
        emit Finished( m_layer, m_nJobType );
      }
    }
    else
    {
      LayerMRI* mri = qobject_cast<LayerMRI*>( m_layer );
      if ( !mri )
      {
        return;
      }
      if ( !mri->LoadVolumeFromFile() )
      {
        emit Error( m_layer, m_nJobType );
      }
      else
      {
        emit Finished( m_layer, m_nJobType );
      }
    }
  }
  else if (m_nJobType == JT_SaveVolume)
  {
    LayerMRI* mri = qobject_cast<LayerMRI*>( m_layer );
    if ( !mri )
    {
      return;
    }
    if ( !mri->SaveVolume() )
    {
      emit Error( m_layer, m_nJobType );
    }
    else
    {
      emit Finished( m_layer, m_nJobType );
    }
  }
  else if ( m_nJobType == JT_LoadSurface )
  {
    LayerSurface* surf = qobject_cast<LayerSurface*>( m_layer );
    if ( !surf )
    {
      return;
    }
    if ( !surf->LoadSurfaceFromFile() )
    {
      emit Error( m_layer, m_nJobType );
    }
    else
    {
      emit Finished( m_layer, m_nJobType );
    }
  }
  else if ( m_nJobType == JT_LoadSurfaceOverlay )
  {
    LayerSurface* surf = qobject_cast<LayerSurface*>( m_layer );
    if ( !surf )
    {
      return;
    }
    QString fn = m_args["FileName"].toString();
    bool bCorrelation = m_args["Correlation"].toBool();
    if ( !surf->LoadOverlayFromFile(fn, bCorrelation))
    {
      emit Error( m_layer, m_nJobType );
    }
    else
    {
      emit Finished( m_layer, m_nJobType );
    }
  }
  else if ( m_nJobType == JT_LoadTrack )
  {
    LayerTrack* layer = qobject_cast<LayerTrack*>( m_layer );
    if ( !layer )
    {
      return;
    }
    connect(layer, SIGNAL(Progress(int)), this, SIGNAL(Progress(int)));
    if ( !layer->LoadTrackFromFile() )
    {
      emit Error( m_layer, m_nJobType );
    }
    else
    {
      emit Finished( m_layer, m_nJobType );
    }
  }
}
