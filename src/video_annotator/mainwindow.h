/// @file
/// @brief Defines MainWindow class for video annotator.

#ifndef VIDEO_ANNOTATOR_MAINWINDOW_H
#define VIDEO_ANNOTATOR_MAINWINDOW_H

#include <memory>
#include <atomic>

#include <QMainWindow>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QColor>
#include <QFileDialog>
#include <QMessageBox>
#include <QThread>
#include <QMap>
#include <QProgressDialog>

#include "species_controls.h"
#include "annotation_widget.h"
#include "global_state_widget.h"
#include "annotation_view.h"
#include "annotation_scene.h"
#include "metadata.h"
#include "video_annotation.h"
#include "player.h"
#include "ui_mainwindow.h"

#ifndef NO_TESTING
class TestVideoAnnotator;
#endif

namespace tator { namespace video_annotator {

/// Video annotation GUI.
class MainWindow : public QMainWindow {
  Q_OBJECT
#ifndef NO_TESTING
  friend class ::TestVideoAnnotator;
#endif
public:
  /// Constructor.
  ///
  /// @param parent Parent widget.
  explicit MainWindow(QWidget *parent = 0);
protected:
  /// Resizes the video and scene.
  ///
  /// @param event Qt resize event pointer.
  void resizeEvent(QResizeEvent *event) override final;
public slots:
  /// Displays a video frame.
  ///
  /// @param image Video frame to display.
  /// @param frame Frame of the image.
  void showFrame(QImage image, qint64 frame);

  /// Adds an individual and enables bounding box drawing.
  ///
  /// @param species Species name of the new individual.
  /// @param subspecies Subspecies name of the new individual.
  void addIndividual(std::string species, std::string subspecies);

  /// Handles color change for a species.
  ///
  /// @param color_map Map between species names and colors.
  void colorChanged(QMap<QString, QColor> color_map);

  /// Handles player duration change.
  ///
  /// @param duration New video duration in total frames.
  void handlePlayerDurationChanged(qint64 duration);

  /// Handles player playback rate change.
  ///
  /// @param rate New playback rate in fps.
  void handlePlayerPlaybackRateChanged(double rate);

  /// Handles player resolution change.
  ///
  /// @param width Width of new video resolution.
  /// @param height Height of new video resolution.
  void handlePlayerResolutionChanged(qint64 width, qint64 height);

  /// Handles player state change.
  ///
  /// @param stopped True if player stopped, false otherwise.
  void handlePlayerStateChanged(bool stopped);

  /// Handles start of media load by creating a progress dialog.
  ///
  /// @param max_progress Maximum value of the progress bar.
  void handlePlayerMediaLoadStart(int max_progress);

  /// Handles file open progress update.
  ///
  /// @param progress Progress update.
  void handlePlayerLoadProgress(int progress);

  /// Handles new media loaded.
  ///
  /// @param video_path Path to loaded video.
  /// @param native_rate Native playback rate of the video.
  void handlePlayerMediaLoaded(QString video_path, qreal native_rate);

  /// Handles media player errors.
  ///
  /// @param err Error message.
  void handlePlayerError(QString err);

  /// Adds a box annotation.
  ///
  /// @param rect Definition of the box.
  void addBoxAnnotation(const QRectF &rect);

  /// Adds a line annotation.
  ///
  /// @param line Definition of the line.
  void addLineAnnotation(const QLineF &line);

  /// Adds a dot annotation.
  ///
  /// @param dot Definition of the dot.
  void addDotAnnotation(const QPointF &dot);

signals:
  /// Requests play.
  void requestPlay();

  /// Requests stop.
  void requestStop();

  /// Requests load video.
  ///
  /// @param file Full path to file to be loaded.
  void requestLoadVideo(QString file);

  /// Requests speed up.
  void requestSpeedUp();

  /// Requests slow down.
  void requestSlowDown();

  /// Requests set frame.
  ///
  /// @param value Frame to go to.
  void requestSetFrame(qint64 value);

  /// Requests next frame.
  void requestNextFrame();

  /// Requests previous frame.
  void requestPrevFrame();
private slots:
  /// Plays/pauses the video.
  void on_play_clicked();

  /// Increases the playback speed of the video by a factor of two.
  void on_faster_clicked();

  /// Decreases the playback speed of the video by a factor of two.
  void on_slower_clicked();

  /// Rewinds the video by one second.
  void on_minusOneSecond_clicked();

  /// Rewinds the video by three seconds.
  void on_minusThreeSecond_clicked();

  /// Increments the video by one frame.
  void on_plusOneFrame_clicked();

  /// Decrements the video by one frame.
  void on_minusOneFrame_clicked();

  /// Loads a video file.
  void on_loadVideo_triggered();

  /// Loads an annotation file.
  void on_loadAnnotationFile_triggered();

  /// Saves an annotation file.
  void on_saveAnnotationFile_triggered();

  /// Writes the current frame to file.
  void on_writeImage_triggered();

  /// Sets metadata for the annotation.
  void on_setMetadata_triggered();

  /// Pauses the video and stores the play/pause state.
  void on_videoSlider_sliderPressed();

  /// Continues the video if it was previously playing.
  void on_videoSlider_sliderReleased();

  /// Sets the current frame to a new position.
  ///
  /// @param action Action that was done.
  void on_videoSlider_actionTriggered(int action);

  /// Updates the current track with a new species and updates the
  ///        subtype options.
  ///
  /// @param text Selected species.
  void on_typeMenu_activated(const QString &text);

  /// Updates the current track with a new subspecies.
  ///
  /// @param text Selected subspecies.
  void on_subTypeMenu_activated(const QString &text);

  /// Updates the active track based on selected ID.
  ///
  /// @param text Selected ID.
  void on_trackNumVal_activated(const QString &text);

  /// Updates the current track with a new count label.
  ///
  /// @param text Selected count label.
  void on_countLabelMenu_activated(const QString &text);

  /// Sets current track to next lowest ID.
  void on_prevTrack_clicked();

  /// Sets current track to next highest ID.
  void on_nextTrack_clicked();

  /// Removes the current track.
  void on_removeTrack_clicked();

  /// Goes to the first frame where a detection for this track
  ///        occurs, if any.
  void on_goToFrame_clicked();

  /// Reassigns ID of current track to another ID.
  void on_reassignTrack_clicked();

  /// Updates the current track to the specified ID.
  void on_goToTrackVal_returnPressed();

  /// Updates the current frame.
  void on_goToFrameVal_returnPressed();

  /// Adds a region for the current track.  If a region already
  ///        exists for this track and frame, an error is raised.
  void on_addRegion_clicked();

  /// Removes a region for the current track and frame.  If a
  ///        region does not exist an error is raised.
  void on_removeRegion_clicked();

  /// Goes to next frame and copies the region corresponding to
  ///        the current track and frame.
  void on_nextAndCopy_clicked();

  /// Redraws annotations.
  void on_viewId_changed();

  /// Redraws annotations.
  void on_viewSpecies_changed();

  /// Redraws annotations.
  void on_viewProbability_changed();

  /// Redraws annotations.
  void on_viewCount_changed();

  /// Records a change to global states.
  void onGlobalStateChange();

  /// Sets current active annotation
  void setItemActive(const QGraphicsItem &item);

  /// Deletes current active annotation
  void deleteCurrentAnn();

private:
  /// Annotations associated with this video.
  std::unique_ptr<VideoAnnotation> annotation_;

  /// Video window.
  std::unique_ptr<AnnotationView> view_;

  /// Scene for displaying video.
  std::unique_ptr<AnnotationScene> scene_;

  /// Pixmap item for displaying video frames.
  QGraphicsPixmapItem *pixmap_item_;

  /// Count text.
  QGraphicsTextItem* count_text_;

  /// Widget loaded from the ui file.
  std::unique_ptr<Ui::MainWindow> ui_;

  /// Species controls widget.
  std::unique_ptr<SpeciesControls> species_controls_;

  /// Annotation widget.
  std::unique_ptr<AnnotationWidget> annotation_widget_;

  /// Global state widget.
  std::unique_ptr<GlobalStateWidget> global_state_widget_;

  /// Current global state annotations.
  std::shared_ptr<GlobalStateAnnotation> current_global_state_;

  /// Load progress dialog.
  std::unique_ptr<QProgressDialog> load_progress_;

  /// Path to loaded video.
  QString video_path_;

  /// Video width.
  qint64 width_;

  /// Video height.
  qint64 height_;

  /// Last frame displayed by player.
  QImage last_frame_;

  /// Last video position (frames).
  qint64 last_position_;

  /// Whether player is stopped.
  bool stopped_;

  /// Whether player was stopped before slider press.
  bool was_stopped_;

  /// Current playback rate.
  double rate_;

  /// Native playback rate.
  double native_rate_;

  /// Currently selected track ID.
  qint64 track_id_;

  /// Current annotations.
  std::list<std::pair<uint64_t, QGraphicsItem*>> current_annotations_;

  /// Annotation metadata.
  Metadata metadata_;

  /// Path to save images using Write Image
  QString images_save_path_;

  /// Map of species names to colors.
  QMap<QString, QColor> color_map_;

  /// True when zoom needs to be reset.
  bool zoom_reset_needed_;

  /// Updates counts of each species in species controls.
  void updateSpeciesCounts();

  /// Updates displayed track statistics.
  void updateStats();

  /// Draws annotations for the last displayed frame.
  void drawAnnotations();

  /// Converts a frame number to a formatted time string.
  QString frameToTime(qint64 frame_number);

  /// Retrieves color for annotation.
  ///
  /// @param id Track ID.
  QColor getColor(qint64 id);

  /// Retrieves species for annotation.
  ///
  /// @param id Track ID.
  std::string getSpecies(qint64 id);

  /// Initializes global state annotations by setting first frame
  /// to the default.
  void initGlobalStateAnnotations();
};

}} // namespace tator::video_annotator

#endif //VIDEO_ANNOTATOR_MAINWINDOW_H
