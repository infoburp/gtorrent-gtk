#include "GtkStatusBox.hpp"
#include <gtkmm/hvseparator.h>
#include <gtorrent/Torrent.hpp>

// TODO: remove all this boilerplate and replace it with initialize methods instead of doing the same thing a dozen times

GtkStatusBox::GtkStatusBox()
{
	set_column_spacing(10);

	m_transfer.set_markup("<big>\nTransfer</big>");
	m_transfer.set_alignment(0.0, 0.5);
	attach(m_transfer             , 0 , 0 , 6 , 1);

	m_time_elapsed_label.set_markup("<b>Time Elapsed:</b>");
	m_time_elapsed_label.set_alignment(1.0, 0.5);
	attach(m_time_elapsed_label   , 0 , 1 , 1 , 1);
	m_time_elapsed.set_alignment(0.0, 0.5);
	attach(m_time_elapsed         , 1 , 1 , 1 , 1);

	m_share_ratio_label.set_markup("<b>Share Ratio:</b>");
	m_share_ratio_label.set_alignment(1.0, 0.5);
	attach(m_share_ratio_label    , 2 , 1 , 1 , 1);
	m_share_ratio.set_alignment(0.0, 0.5);
	attach(m_share_ratio          , 3 , 1 , 1 , 1);

	m_remaining_label.set_markup("<b>Remaining:</b>");
	m_remaining_label.set_alignment(1.0, 0.5);
	attach(m_remaining_label      , 4 , 1 , 1 , 1);
	m_remaining.set_alignment(0.0, 0.5);
	attach(m_remaining            , 5 , 1 , 1 , 1);

	m_downloaded_label.set_markup("<b>Downloaded:</b>");
	m_downloaded_label.set_alignment(1.0, 0.5);
	attach(m_downloaded_label     , 0 , 2 , 1 , 1);
	m_downloaded.set_alignment(0.0, 0.5);
	attach(m_downloaded           , 1 , 2 , 1 , 1);

	m_download_speed_label.set_markup("<b>Download Speed:</b>");
	m_download_speed_label.set_alignment(1.0, 0.5);
	attach(m_download_speed_label , 2 , 2 , 1 , 1);
	m_download_speed.set_alignment(0.0, 0.5);
	attach(m_download_speed       , 3 , 2 , 1 , 1);

	m_down_limit_label.set_markup("<b>Down Limit:</b>");
	m_down_limit_label.set_alignment(1.0, 0.5);
	attach(m_down_limit_label     , 4 , 2 , 1 , 1);
	m_down_limit.set_alignment(0.0, 0.5);
	attach(m_down_limit           , 5 , 2 , 1 , 1);

	m_uploaded_label.set_markup("<b>Uploaded:</b>");
	m_uploaded_label.set_alignment(1.0, 0.5);
	attach(m_uploaded_label     , 0 , 3 , 1 , 1);
	m_uploaded.set_alignment(0.0, 0.5);
	attach(m_uploaded           , 1 , 3 , 1 , 1);

	m_upload_speed_label.set_markup("<b>Upload Speed:</b>");
	m_upload_speed_label.set_alignment(1.0, 0.5);
	attach(m_upload_speed_label , 2 , 3 , 1 , 1);
	m_upload_speed.set_alignment(0.0, 0.5);
	attach(m_upload_speed       , 3 , 3 , 1 , 1);

	m_up_limit_label.set_markup("<b>Up Limit:</b>");
	m_up_limit_label.set_alignment(1.0, 0.5);
	attach(m_up_limit_label     , 4 , 3 , 1 , 1);
	m_up_limit.set_alignment(0.0, 0.5);
	attach(m_up_limit           , 5 , 3 , 1 , 1);

	m_tracker.set_markup("<big>\nTracker</big>");
	m_tracker.set_alignment(0.0, 0.5);
	attach(m_tracker             , 0 , 4 , 6 , 1);

	m_tracker_url_label.set_markup("<b>Tracker URL:</b>");
	m_tracker_url_label.set_alignment(1.0, 0.5);
	attach(m_tracker_url_label     , 0 , 5 , 1 , 1);
	m_tracker_url.set_alignment(0.0, 0.5);
	attach(m_tracker_url           , 1 , 5 , 1 , 1);

	m_tracker_status_label.set_markup("<b>Tracker Status:</b>");
	m_tracker_status_label.set_alignment(1.0, 0.5);
	attach(m_tracker_status_label     , 2 , 5 , 1 , 1);
	m_tracker_status.set_alignment(0.0, 0.5);
	attach(m_tracker_status           , 3 , 5 , 1 , 1);

	m_general.set_markup("<big>\nGeneral</big>");
	m_general.set_alignment(0.0, 0.5);
	attach(m_general             , 0 , 6 , 6 , 1);

	m_save_as_label.set_markup("<b>Save As:</b>");
	m_save_as_label.set_alignment(1.0, 0.5);
	attach(m_save_as_label     , 0 , 7 , 1 , 1);
	m_save_as.set_alignment(0.0, 0.5);
	attach(m_save_as           , 1 , 7 , 1 , 1);

	m_total_size_label.set_markup("<b>Total Size:</b>");
	m_total_size_label.set_alignment(1.0, 0.5);
	attach(m_total_size_label     , 0 , 8 , 1 , 1);
	m_total_size.set_alignment(0.0, 0.5);
	attach(m_total_size           , 1 , 8 , 1 , 1);

	m_pieces_label.set_markup("<b>Pieces:</b>");
	m_pieces_label.set_alignment(1.0, 0.5);
	attach(m_pieces_label     , 2 , 8 , 1 , 1);
	m_pieces.set_alignment(0.0, 0.5);
	attach(m_pieces           , 3 , 8 , 1 , 1);

	m_hash_label.set_markup("<b>Hash:</b>");
	m_hash_label.set_alignment(1.0, 0.5);
	attach(m_hash_label     , 0 , 9 , 1 , 1);
	m_hash.set_alignment(0.0, 0.5);
	attach(m_hash           , 1 , 9 , 1 , 1);
}

void GtkStatusBox::update(std::shared_ptr<gt::Torrent> selected)
{
	m_time_elapsed.set_text(selected->getTextActiveTime());
	m_remaining.set_text(selected->getTextEta());
	m_share_ratio.set_text(std::to_string(selected->getTotalRatio()));

	m_downloaded.set_text(selected->getTextTotalDownloaded());
	m_download_speed.set_text(selected->getTextDownloadRate());
	m_down_limit.set_text("");

	m_uploaded.set_text(selected->getTextTotalUploaded());
	m_upload_speed.set_text(selected->getTextUploadRate());
	m_up_limit.set_text("");

	m_tracker_url.set_text(selected->getCurrentTrackerURL());
	m_tracker_status.set_text("");

	m_save_as.set_text(selected->getSavePath());

	m_total_size.set_text(selected->getTextSize());
	m_pieces.set_text(std::to_string(selected->getPieces().size()));

	m_hash.set_text(selected->getFormattedHash());
}