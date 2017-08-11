/// @file
/// @brief Defines ReassignDialog class.

#ifndef REASSIGN_DIALOG_H
#define REASSIGN_DIALOG_H

#include <memory>

#include <QWidget>
#include <QDialog>

#include "../../src/video_annotator/ui_reassign_dialog.h"

namespace fish_annotator { namespace video_annotator {

struct Reassignment {
  uint32_t from_id_; ///< ID to reassign.
  uint32_t to_id_; ///< ID to reassign to.
  uint64_t from_frame_; ///< Frame to start reassignment.
  uint64_t to_frame_; ///< Frame to stop reassignment.
};

class ReassignDialog : public QDialog {
  Q_OBJECT
public:
  /// @brief Constructor.
  ///
  /// @param parent Parent widget.
  explicit ReassignDialog(QWidget *parent = 0);

  /// @brief Returns a reassignment object corresponding to the dialog
  ///        values.
  /// @return Reassignment object corresponding to dialog values.
  Reassignment getReassignment();

private slots:
  /// @brief Calls inherited accept function.
  void on_ok_clicked();

  /// @brief Calls inherited reject function.
  void on_cancel_clicked();

  /// @brief Updates ID for new track checked/unchecked.
  void on_newTrack_stateChanged(int state);

  /// @brief Updates frame according to presets.
  void on_framePresets_currentIndexChanged(const QString &text);

private:
  /// @brief Dialog loaded from ui file.
  std::unique_ptr<Ui::ReassignDialog> ui_;
};

}} // namespace fish_annotator::video_annotator

#endif // REASSIGN_DIALOG_H
