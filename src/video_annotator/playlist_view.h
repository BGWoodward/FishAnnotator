#ifndef PLAYLIST_VIEW_H
#define PLAYLIST_VIEW_H



#include "ui_playlist_view.h"

#include "playlist.h"

#include <memory>

namespace tator
{

  class PlaylistView : public QDockWidget {
    Q_OBJECT
  public:
    explicit PlaylistView(QWidget *parent = nullptr);
Playlist *playlist() {return playlist_.get();}
  private:
    std::unique_ptr<Ui::PlaylistView> ui_;
    std::unique_ptr<Playlist> playlist_;
  };

} //namespace tator
#endif