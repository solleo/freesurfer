/**
 * @file  DialogCropVolume.h
 * @brief REPLACE_WITH_ONE_LINE_SHORT_DESCRIPTION
 *
 */
/*
 * Original Author: Ruopeng Wang
 * CVS Revision Info:
 *    $Author: nicks $
 *    $Date: 2011/03/14 23:44:46 $
 *    $Revision: 1.8 $
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
#ifndef DIALOGCROPVOLUME_H
#define DIALOGCROPVOLUME_H

#include <QDialog>

namespace Ui
{
class DialogCropVolume;
}

class Layer;
class LayerMRI;
class QSpinBox;

class DialogCropVolume : public QDialog
{
  Q_OBJECT
public:
  explicit DialogCropVolume(QWidget *parent = 0, LayerMRI* layer = 0);
  ~DialogCropVolume();

  void SetVolume( LayerMRI* mri );

protected slots:
  void OnCropBoundChanged(LayerMRI* mri);
  void OnLayerRemoved(Layer* layer);
  void OnSpinRange      (int nVal);
  void showEvent(QShowEvent *);
  void hideEvent(QHideEvent *);

private:
  Ui::DialogCropVolume *ui;
  QSpinBox*   m_spinRange[6];

  LayerMRI*   m_mri;
  bool        m_bShowSliceFrame;
};

#endif // DIALOGCROPVOLUME_H
