#include "playlist_view.h"

namespace tator {

  PlaylistView::PlaylistView(QWidget *parent) :
    QDockWidget(parent)
    , ui_(new Ui::PlaylistView)
    , playlist_(new Playlist(this))
  {
    ui_->setupUi(this);
    ui_->treeView->setModel(playlist_.get());
  }
}