#include "GtkTorrentInfoBar.hpp"

#include <gtkmm/table.h>
#include <gtkmm/hvseparator.h>

/**
* Sets up the torrent info bar.
*/
	GtkTorrentInfoBar::GtkTorrentInfoBar()
	: Gtk::Box(Gtk::ORIENTATION_VERTICAL)
{
	m_notebook 											= Gtk::manage			(new Gtk::Notebook																											 ());

	m_time_box 											= Gtk::manage			(new Gtk::Box																		(Gtk::ORIENTATION_VERTICAL));
	m_file_box											= Gtk::manage			(new Gtk::Box																		(Gtk::ORIENTATION_VERTICAL));
	m_network_box 									= Gtk::manage			(new Gtk::Box																		(Gtk::ORIENTATION_VERTICAL));
	m_peer_box											= Gtk::manage			(new Gtk::Box																		(Gtk::ORIENTATION_VERTICAL));
	m_bool_box 											= Gtk::manage			(new Gtk::Box																		(Gtk::ORIENTATION_VERTICAL));

	m_piece_box 										= Gtk::manage			(new Gtk::Box																		(Gtk::ORIENTATION_VERTICAL));

	m_title 												= Gtk::manage			(new 																													Gtk::Label());

	this														->pack_start			(*m_title, 																								Gtk::PACK_SHRINK);

	m_progress 											= Gtk::manage			(new 																														GtkPiece());
	m_graph 												= Gtk::manage			(new 																														GtkGraph());

	m_piece_box											->pack_end				(*m_progress, 																	Gtk::PACK_EXPAND_WIDGET, 0);
	m_progress											->set_size_request(0, 30);

	m_file_box											->add							(*m_piece_box);

	m_time_table_layout 						= Gtk::manage			(new Gtk::Table																							(12, 2, false));
	m_time_table_layout							->set_col_spacings(5);

	m_file_table_layout 						= Gtk::manage			(new Gtk::Table																							(17, 2, false));
	m_file_table_layout							->set_col_spacings(5);

	m_network_table_layout 					= Gtk::manage			(new Gtk::Table																							(16, 2, false));
	m_network_table_layout					->set_col_spacings(5);

	m_peer_table_layout 						= Gtk::manage			(new Gtk::Table																							(8, 2, false));
	m_peer_table_layout							->set_col_spacings(5);

	m_bool_table_layout 						= Gtk::manage			(new Gtk::Table																							(14, 2, false));
	m_bool_table_layout							->set_col_spacings(5);

	m_eta_label 										= Gtk::manage			(new Gtk::Label());
	m_eta_label											->set_markup			("<b>eta</b>");
	m_eta 													= Gtk::manage			(new Gtk::Label());
	m_time_table_layout							->attach					(*m_eta_label, 											0, 1, 0, 1, Gtk::AttachOptions::SHRINK);
	m_time_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2, 0, 1, Gtk::AttachOptions::SHRINK);
	m_time_table_layout							->attach					(*m_eta, 														2, 3, 0, 1, Gtk::AttachOptions::SHRINK);

	m_active_time_label 						= Gtk::manage			(new Gtk::Label());
	m_active_time_label							->set_markup			("<b>active time</b>");
	m_active_time 									= Gtk::manage			(new Gtk::Label());
	m_time_table_layout							->attach					(*m_active_time_label, 							0, 1, 1, 2, Gtk::AttachOptions::SHRINK);
	m_time_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2, 1, 2, Gtk::AttachOptions::SHRINK);
	m_time_table_layout							->attach					(*m_active_time, 										2, 3, 1, 2, Gtk::AttachOptions::SHRINK);

	m_added_time_label 							= Gtk::manage			(new Gtk::Label());
	m_added_time_label							->set_markup			("<b>added time</b>");
	m_added_time 										= Gtk::manage			(new Gtk::Label());
	m_time_table_layout							->attach					(*m_added_time_label, 							0, 1, 2, 3, Gtk::AttachOptions::SHRINK);
	m_time_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2, 2, 3, Gtk::AttachOptions::SHRINK);
	m_time_table_layout							->attach					(*m_added_time, 										2, 3, 2, 3, Gtk::AttachOptions::SHRINK);

	m_next_announce_label 					= Gtk::manage			(new Gtk::Label());
	m_next_announce_label						->set_markup			("<b>announce</b>");
	m_next_announce 								= Gtk::manage			(new Gtk::Label("0"));
	m_time_table_layout							->attach					(*m_next_announce_label, 						0, 1, 3, 4, Gtk::AttachOptions::SHRINK);
	m_time_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2, 3, 4, Gtk::AttachOptions::SHRINK);
	m_time_table_layout							->attach					(*m_next_announce, 									2, 3, 3, 4, Gtk::AttachOptions::SHRINK);

	m_announce_interval_label				= Gtk::manage			(new Gtk::Label());
	m_announce_interval_label				->set_markup			("<b>interval</b>");
	m_announce_interval 						= Gtk::manage			(new Gtk::Label());
	m_time_table_layout							->attach					(*m_announce_interval_label, 				0, 1, 4, 5, Gtk::AttachOptions::SHRINK);
	m_time_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2, 4, 5, Gtk::AttachOptions::SHRINK);
	m_time_table_layout							->attach					(*m_announce_interval, 							2, 3, 4, 5, Gtk::AttachOptions::SHRINK);

	m_completed_time_label 					= Gtk::manage			(new Gtk::Label());
	m_completed_time_label					->set_markup			("<b>completed time</b>");
	m_completed_time 								= Gtk::manage			(new Gtk::Label());
	m_time_table_layout							->attach					(*m_completed_time_label, 					0, 1, 5, 6, Gtk::AttachOptions::SHRINK);
	m_time_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2, 5, 6, Gtk::AttachOptions::SHRINK);
	m_time_table_layout							->attach					(*m_completed_time, 								2, 3, 5, 6, Gtk::AttachOptions::SHRINK);

	m_finished_time_label 					= Gtk::manage			(new Gtk::Label());
	m_finished_time_label						->set_markup			("<b>finished time</b>");
	m_finished_time 								= Gtk::manage			(new Gtk::Label());
	m_time_table_layout							->attach					(*m_finished_time_label, 						0, 1, 6, 7, Gtk::AttachOptions::SHRINK);
	m_time_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2, 6, 7, Gtk::AttachOptions::SHRINK);
	m_time_table_layout							->attach					(*m_finished_time, 									2, 3, 6, 7, Gtk::AttachOptions::SHRINK);

	m_seeding_time_label 						= Gtk::manage			(new Gtk::Label());
	m_seeding_time_label						->set_markup			("<b>seeding time</b>");
	m_seeding_time 									= Gtk::manage			(new Gtk::Label());
	m_time_table_layout							->attach					(*m_seeding_time_label, 						0, 1, 7, 8, Gtk::AttachOptions::SHRINK);
	m_time_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2, 7, 8, Gtk::AttachOptions::SHRINK);
	m_time_table_layout							->attach					(*m_seeding_time, 									2, 3, 7, 8, Gtk::AttachOptions::SHRINK);

	m_last_scrape_label 						= Gtk::manage			(new Gtk::Label());
	m_last_scrape_label							->set_markup			("<b>last scrape</b>");
	m_last_scrape 									= Gtk::manage			(new Gtk::Label());
	m_time_table_layout							->attach					(*m_last_scrape_label, 							0, 1, 8, 9, Gtk::AttachOptions::SHRINK);
	m_time_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2, 8, 9, Gtk::AttachOptions::SHRINK);
	m_time_table_layout							->attach					(*m_last_scrape, 										2, 3, 8, 9, Gtk::AttachOptions::SHRINK);

	m_last_seen_complete_label 			= Gtk::manage			(new Gtk::Label());
	m_last_seen_complete_label			->set_markup			("<b>last seen complete</b>");
	m_last_seen_complete 						= Gtk::manage			(new Gtk::Label());
	m_time_table_layout							->attach					(*m_last_seen_complete_label, 			0, 1, 9,10, Gtk::AttachOptions::SHRINK);
	m_time_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2, 9,10, Gtk::AttachOptions::SHRINK);
	m_time_table_layout							->attach					(*m_last_seen_complete, 						2, 3, 9,10, Gtk::AttachOptions::SHRINK);

	m_time_since_upload_label 			= Gtk::manage			(new Gtk::Label());
	m_time_since_upload_label				->set_markup			("<b>time since upload</b>");
	m_time_since_upload 						= Gtk::manage			(new Gtk::Label());
	m_time_table_layout							->attach					(*m_time_since_upload_label, 				0, 1,10,11, Gtk::AttachOptions::SHRINK);
	m_time_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2,10,11, Gtk::AttachOptions::SHRINK);
	m_time_table_layout							->attach					(*m_time_since_upload, 							2, 3,10,11, Gtk::AttachOptions::SHRINK);

	m_time_since_download_label 		= Gtk::manage			(new Gtk::Label());
	m_time_since_download_label			->set_markup			("<b>time since download</b>");
	m_time_since_download 					= Gtk::manage			(new Gtk::Label());
	m_time_table_layout							->attach					(*m_time_since_download_label, 			0, 1,11,12, Gtk::AttachOptions::SHRINK);
	m_time_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2,11,12, Gtk::AttachOptions::SHRINK);
	m_time_table_layout							->attach					(*m_time_since_download, 						2, 3,11,12, Gtk::AttachOptions::SHRINK);

	m_info_hash_label 							= Gtk::manage			(new Gtk::Label());
	m_info_hash_label								->set_markup			("<b>info hash</b>");
	m_info_hash 										= Gtk::manage			(new Gtk::Label());
	m_file_table_layout							->attach					(*m_info_hash_label, 								0, 1, 0, 1, Gtk::AttachOptions::SHRINK);
	m_file_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2, 0, 1, Gtk::AttachOptions::SHRINK);
	m_file_table_layout							->attach					(*m_info_hash, 											2, 3, 0, 1, Gtk::AttachOptions::SHRINK);

	m_torrent_file_label 						= Gtk::manage			(new Gtk::Label());
	m_torrent_file_label						->set_markup			("<b>torrent</b>");
	m_torrent_file 									= Gtk::manage			(new Gtk::Label("0"));
	m_file_table_layout							->attach					(*m_torrent_file_label, 						0, 1, 1, 2, Gtk::AttachOptions::SHRINK);
	m_file_table_layout							->attach					(*(new Gtk::VSeparator()),				 	1, 2, 1, 2, Gtk::AttachOptions::SHRINK);
	m_file_table_layout							->attach					(*m_torrent_file, 									2, 3, 1, 2, Gtk::AttachOptions::SHRINK);

	m_save_path_label 							= Gtk::manage			(new Gtk::Label());
	m_save_path_label								->set_markup			("<b>path</b>");
	m_save_path 										= Gtk::manage			(new Gtk::Label("0"));
	m_file_table_layout							->attach					(*m_save_path_label, 								0, 1, 2, 3, Gtk::AttachOptions::SHRINK);
	m_file_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2, 2, 3, Gtk::AttachOptions::SHRINK);
	m_file_table_layout							->attach					(*m_save_path, 											2, 3, 2, 3, Gtk::AttachOptions::SHRINK);

	m_num_pieces_label 							= Gtk::manage			(new Gtk::Label());
	m_num_pieces_label							->set_markup			("<b>pieces</b>");
	m_num_pieces 										= Gtk::manage			(new Gtk::Label());
	m_file_table_layout							->attach					(*m_num_pieces_label, 							0, 1, 3, 4, Gtk::AttachOptions::SHRINK);
	m_file_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2, 3, 4, Gtk::AttachOptions::SHRINK);
	m_file_table_layout							->attach					(*m_num_pieces, 										2, 3, 3, 4, Gtk::AttachOptions::SHRINK);

	m_block_size_label 							= Gtk::manage			(new Gtk::Label());
	m_block_size_label							->set_markup			("<b>piece size</b>");
	m_block_size 										= Gtk::manage			(new Gtk::Label());
	m_file_table_layout							->attach					(*m_block_size_label, 							0, 1, 4, 5, Gtk::AttachOptions::SHRINK);
	m_file_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2, 4, 5, Gtk::AttachOptions::SHRINK);
	m_file_table_layout							->attach					(*m_block_size, 										2, 3, 4, 5, Gtk::AttachOptions::SHRINK);

	m_total_wanted_label 						= Gtk::manage			(new Gtk::Label());
	m_total_wanted_label						->set_markup			("<b>size</b>");
	m_total_wanted 									= Gtk::manage			(new Gtk::Label());
	m_file_table_layout							->attach					(*m_total_wanted_label, 						0, 1, 5, 6, Gtk::AttachOptions::SHRINK);
	m_file_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2, 5, 6, Gtk::AttachOptions::SHRINK);
	m_file_table_layout							->attach					(*m_total_wanted, 									2, 3, 5, 6, Gtk::AttachOptions::SHRINK);

	m_total_wanted_done_label 			= Gtk::manage			(new Gtk::Label());
	m_total_wanted_done_label				->set_markup			("<b>wanted done</b>");
	m_total_wanted_done 						= Gtk::manage			(new Gtk::Label());
	m_file_table_layout							->attach					(*m_total_wanted_done_label, 				0, 1, 6, 7, Gtk::AttachOptions::SHRINK);
	m_file_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2, 6, 7, Gtk::AttachOptions::SHRINK);
	m_file_table_layout							->attach					(*m_total_wanted_done, 							2, 3, 6, 7, Gtk::AttachOptions::SHRINK);

	m_total_done_label 							= Gtk::manage			(new Gtk::Label());
	m_total_done_label							->set_markup			("<b>done</b>");
	m_total_done 										= Gtk::manage			(new Gtk::Label());
	m_file_table_layout							->attach					(*m_total_done_label, 							0, 1, 7, 8, Gtk::AttachOptions::SHRINK);
	m_file_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2, 7, 8, Gtk::AttachOptions::SHRINK);
	m_file_table_layout							->attach					(*m_total_done, 										2, 3, 7, 8, Gtk::AttachOptions::SHRINK);

	m_all_time_download_label 			= Gtk::manage			(new Gtk::Label());
	m_all_time_download_label				->set_markup			("<b>all time download</b>");
	m_all_time_download 						= Gtk::manage			(new Gtk::Label());
	m_file_table_layout							->attach					(*m_all_time_download_label, 				0, 1, 8, 9, Gtk::AttachOptions::SHRINK);
	m_file_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2, 8, 9, Gtk::AttachOptions::SHRINK);
	m_file_table_layout							->attach					(*m_all_time_download, 							2, 3, 8, 9, Gtk::AttachOptions::SHRINK);

	m_down_total_label 							= Gtk::manage			(new Gtk::Label());
	m_down_total_label							->set_markup			("<b>down</b>");
	m_down_total 										= Gtk::manage			(new Gtk::Label());
	m_file_table_layout							->attach					(*m_down_total_label, 							0, 1, 9,10, Gtk::AttachOptions::SHRINK);
	m_file_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2, 9,10, Gtk::AttachOptions::SHRINK);
	m_file_table_layout							->attach					(*m_down_total, 										2, 3, 9,10, Gtk::AttachOptions::SHRINK);

	m_total_payload_download_label 	= Gtk::manage			(new Gtk::Label());
	m_total_payload_download_label	->set_markup			("<b>payload download</b>");
	m_total_payload_download 				= Gtk::manage			(new Gtk::Label());
	m_file_table_layout							->attach					(*m_total_payload_download_label, 	0, 1,10,11, Gtk::AttachOptions::SHRINK);
	m_file_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2,10,11, Gtk::AttachOptions::SHRINK);
	m_file_table_layout							->attach					(*m_total_payload_download, 				2, 3,10,11, Gtk::AttachOptions::SHRINK);

	m_all_time_upload_label 				= Gtk::manage			(new Gtk::Label());
	m_all_time_upload_label					->set_markup			("<b>all time upload</b>");
	m_all_time_upload 							= Gtk::manage			(new Gtk::Label());
	m_file_table_layout							->attach					(*m_all_time_upload_label, 					0, 1,11,12, Gtk::AttachOptions::SHRINK);
	m_file_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2,11,12, Gtk::AttachOptions::SHRINK);
	m_file_table_layout							->attach					(*m_all_time_upload, 								2, 3,11,12, Gtk::AttachOptions::SHRINK);

	m_up_total_label 								= Gtk::manage			(new Gtk::Label());
	m_up_total_label								->set_markup			("<b>up</b>");
	m_up_total 											= Gtk::manage			(new Gtk::Label());
	m_file_table_layout							->attach					(*m_up_total_label, 								0, 1,12,13, Gtk::AttachOptions::SHRINK);
	m_file_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2,12,13, Gtk::AttachOptions::SHRINK);
	m_file_table_layout							->attach					(*m_up_total, 											2, 3,12,13, Gtk::AttachOptions::SHRINK);

	m_total_payload_upload_label 		= Gtk::manage			(new Gtk::Label());
	m_total_payload_upload_label		->set_markup			("<b>payload upload</b>");
	m_total_payload_upload 					= Gtk::manage			(new Gtk::Label());
	m_file_table_layout							->attach					(*m_total_payload_upload_label, 		0, 1,13,14, Gtk::AttachOptions::SHRINK);
	m_file_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2,13,14, Gtk::AttachOptions::SHRINK);
	m_file_table_layout							->attach					(*m_total_payload_upload, 					2, 3,13,14, Gtk::AttachOptions::SHRINK);

	m_total_failed_bytes_label 			= Gtk::manage			(new Gtk::Label());
	m_total_failed_bytes_label			->set_markup			("<b>failed bytes</b>");
	m_total_failed_bytes 						= Gtk::manage			(new Gtk::Label());
	m_file_table_layout							->attach					(*m_total_failed_bytes_label,				0, 1,14,15, Gtk::AttachOptions::SHRINK);
	m_file_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2,14,15, Gtk::AttachOptions::SHRINK);
	m_file_table_layout							->attach					(*m_total_failed_bytes, 						2, 3,14,15, Gtk::AttachOptions::SHRINK);

	m_total_redundant_bytes_label 	= Gtk::manage			(new Gtk::Label());
	m_total_redundant_bytes_label		->set_markup			("<b>redundant bytes</b>");
	m_total_redundant_bytes 				= Gtk::manage			(new Gtk::Label());
	m_file_table_layout							->attach					(*m_total_redundant_bytes_label, 		0, 1,15,16, Gtk::AttachOptions::SHRINK);
	m_file_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2,15,16, Gtk::AttachOptions::SHRINK);
	m_file_table_layout							->attach					(*m_total_redundant_bytes, 					2, 3,15,16, Gtk::AttachOptions::SHRINK);


	m_progress_ppm_label 						= Gtk::manage			(new Gtk::Label());
	m_progress_ppm_label						->set_markup			("<b>progress ppm</b>");
	m_progress_ppm 									= Gtk::manage			(new Gtk::Label());
	m_file_table_layout							->attach					(*m_progress_ppm_label, 						0, 1,16,17, Gtk::AttachOptions::SHRINK);
	m_file_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2,16,17, Gtk::AttachOptions::SHRINK);
	m_file_table_layout							->attach					(*m_progress_ppm, 									2, 3,16,17, Gtk::AttachOptions::SHRINK);

	m_state_label 									= Gtk::manage			(new Gtk::Label());
	m_state_label										->set_markup			("<b>state</b>");
	m_state 												= Gtk::manage			(new Gtk::Label());
	m_network_table_layout					->attach					(*m_state_label, 										0, 1, 0, 1, Gtk::AttachOptions::SHRINK);
	m_network_table_layout					->attach					(*(new Gtk::VSeparator()), 					1, 2, 0, 1, Gtk::AttachOptions::SHRINK);
	m_network_table_layout					->attach					(*m_state, 													2, 3, 0, 1, Gtk::AttachOptions::SHRINK);

	m_current_tracker_label 				= Gtk::manage			(new Gtk::Label());
	m_current_tracker_label					->set_markup			("<b>tracker</b>");
	m_current_tracker 							= Gtk::manage			(new Gtk::Label());
	m_network_table_layout					->attach					(*m_current_tracker_label, 					0, 1, 1, 2, Gtk::AttachOptions::SHRINK);
	m_network_table_layout					->attach					(*(new Gtk::VSeparator()), 					1, 2, 1, 2, Gtk::AttachOptions::SHRINK);
	m_network_table_layout					->attach					(*m_current_tracker, 								2, 3, 1, 2, Gtk::AttachOptions::SHRINK);

	m_seed_rank_label 							= Gtk::manage			(new Gtk::Label());
	m_seed_rank_label								->set_markup			("<b>seed rank</b>");
	m_seed_rank 										= Gtk::manage			(new Gtk::Label());
	m_network_table_layout					->attach					(*m_seed_rank_label, 								0, 1, 2, 3, Gtk::AttachOptions::SHRINK);
	m_network_table_layout					->attach					(*(new Gtk::VSeparator()), 					1, 2, 2, 3, Gtk::AttachOptions::SHRINK);
	m_network_table_layout					->attach					(*m_seed_rank, 											2, 3, 2, 3, Gtk::AttachOptions::SHRINK);

	m_queue_position_label 					= Gtk::manage			(new Gtk::Label());
	m_queue_position_label					->set_markup			("<b>queue position</b>");
	m_queue_position 								= Gtk::manage			(new Gtk::Label());
	m_network_table_layout					->attach					(*m_queue_position_label, 					0, 1, 3, 4, Gtk::AttachOptions::SHRINK);
	m_network_table_layout					->attach					(*(new Gtk::VSeparator()), 					1, 2, 3, 4, Gtk::AttachOptions::SHRINK);
	m_network_table_layout					->attach					(*m_queue_position, 								2, 3, 3, 4, Gtk::AttachOptions::SHRINK);

	m_download_rate_label						= Gtk::manage			(new Gtk::Label());
	m_download_rate_label						->set_markup			("<b>download</b>");
	m_download_rate 								= Gtk::manage			(new Gtk::Label());
	m_network_table_layout					->attach					(*m_download_rate_label, 						0, 1, 4, 5, Gtk::AttachOptions::SHRINK);
	m_network_table_layout					->attach					(*(new Gtk::VSeparator()), 					1, 2, 4, 5, Gtk::AttachOptions::SHRINK);
	m_network_table_layout					->attach					(*m_download_rate, 									2, 3, 4, 5, Gtk::AttachOptions::SHRINK);

	m_download_payload_rate_label		= Gtk::manage			(new Gtk::Label());
	m_download_payload_rate_label		->set_markup			("<b>download payload</b>");
	m_download_payload_rate 				= Gtk::manage			(new Gtk::Label());
	m_network_table_layout					->attach					(*m_download_payload_rate_label,		0, 1, 5, 6, Gtk::AttachOptions::SHRINK);
	m_network_table_layout					->attach					(*(new Gtk::VSeparator()), 					1, 2, 5, 6, Gtk::AttachOptions::SHRINK);
	m_network_table_layout					->attach					(*m_download_payload_rate, 					2, 3, 5, 6, Gtk::AttachOptions::SHRINK);


	m_down_bandwidth_queue_label 		= Gtk::manage			(new Gtk::Label());
	m_down_bandwidth_queue_label		->set_markup			("<b>download queue</b>");
	m_down_bandwidth_queue 					= Gtk::manage			(new Gtk::Label());
	m_network_table_layout					->attach					(*m_down_bandwidth_queue_label, 		0, 1, 6, 7, Gtk::AttachOptions::SHRINK);
	m_network_table_layout					->attach					(*(new Gtk::VSeparator()), 					1, 2, 6, 7, Gtk::AttachOptions::SHRINK);
	m_network_table_layout					->attach					(*m_down_bandwidth_queue, 					2, 3, 6, 7, Gtk::AttachOptions::SHRINK);

	m_upload_rate_label 						= Gtk::manage			(new Gtk::Label());
	m_upload_rate_label							->set_markup			("<b>upload</b>");
	m_upload_rate 									= Gtk::manage			(new Gtk::Label());
	m_network_table_layout					->attach					(*m_upload_rate_label, 							0, 1, 7, 8, Gtk::AttachOptions::SHRINK);
	m_network_table_layout					->attach					(*(new Gtk::VSeparator()), 					1, 2, 7, 8, Gtk::AttachOptions::SHRINK);
	m_network_table_layout					->attach					(*m_upload_rate, 										2, 3, 7, 8, Gtk::AttachOptions::SHRINK);

	m_upload_payload_rate_label 		= Gtk::manage			(new Gtk::Label());
	m_upload_payload_rate_label			->set_markup			("<b>upload payload</b>");
	m_upload_payload_rate 					= Gtk::manage			(new Gtk::Label());
	m_network_table_layout					->attach					(*m_upload_payload_rate_label, 			0, 1, 8, 9, Gtk::AttachOptions::SHRINK);
	m_network_table_layout					->attach					(*(new Gtk::VSeparator()), 					1, 2, 8, 9, Gtk::AttachOptions::SHRINK);
	m_network_table_layout					->attach					(*m_upload_payload_rate, 						2, 3, 8, 9, Gtk::AttachOptions::SHRINK);

	m_up_bandwidth_queue_label 			= Gtk::manage			(new Gtk::Label());
	m_up_bandwidth_queue_label			->set_markup			("<b>upload queue</b>");
	m_up_bandwidth_queue 						= Gtk::manage			(new Gtk::Label());
	m_network_table_layout					->attach					(*m_up_bandwidth_queue_label, 			0, 1, 9,10, Gtk::AttachOptions::SHRINK);
	m_network_table_layout					->attach					(*(new Gtk::VSeparator()), 					1, 2, 9,10, Gtk::AttachOptions::SHRINK);
	m_network_table_layout					->attach					(*m_up_bandwidth_queue, 						2, 3, 9,10, Gtk::AttachOptions::SHRINK);

	m_num_uploads_label 						= Gtk::manage			(new Gtk::Label());
	m_num_uploads_label							->set_markup			("<b>uploads</b>");
	m_num_uploads 									= Gtk::manage			(new Gtk::Label());
	m_network_table_layout					->attach					(*m_num_uploads_label, 							0, 1,10,11, Gtk::AttachOptions::SHRINK);
	m_network_table_layout					->attach					(*(new Gtk::VSeparator()), 					1, 2,10,11, Gtk::AttachOptions::SHRINK);
	m_network_table_layout					->attach					(*m_num_uploads, 										2, 3,10,11, Gtk::AttachOptions::SHRINK);

	m_uploads_limit_label 					= Gtk::manage			(new Gtk::Label());
	m_uploads_limit_label						->set_markup			("<b>uploads limit</b>");
	m_uploads_limit 								= Gtk::manage			(new Gtk::Label());
	m_network_table_layout					->attach					(*m_uploads_limit_label, 						0, 1,11,12, Gtk::AttachOptions::SHRINK);
	m_network_table_layout					->attach					(*(new Gtk::VSeparator()), 					1, 2,11,12, Gtk::AttachOptions::SHRINK);
	m_network_table_layout					->attach					(*m_uploads_limit, 									2, 3,11,12, Gtk::AttachOptions::SHRINK);

	m_priority_label 								= Gtk::manage			(new Gtk::Label());
	m_priority_label								->set_markup			("<b>priority</b>");
	m_priority 											= Gtk::manage			(new Gtk::Label());
	m_network_table_layout					->attach					(*m_priority_label, 								0, 1,12,13, Gtk::AttachOptions::SHRINK);
	m_network_table_layout					->attach					(*(new Gtk::VSeparator()), 					1, 2,12,13, Gtk::AttachOptions::SHRINK);
	m_network_table_layout					->attach					(*m_priority, 											2, 3,12,13, Gtk::AttachOptions::SHRINK);

	m_num_connections_label 				= Gtk::manage			(new Gtk::Label());
	m_num_connections_label					->set_markup			("<b>connections</b>");
	m_num_connections								= Gtk::manage			(new Gtk::Label());
	m_network_table_layout					->attach					(*m_num_connections_label, 					0, 1,13,14, Gtk::AttachOptions::SHRINK);
	m_network_table_layout					->attach					(*(new Gtk::VSeparator()), 					1, 2,13,14, Gtk::AttachOptions::SHRINK);
	m_network_table_layout					->attach					(*m_num_connections, 								2, 3,13,14, Gtk::AttachOptions::SHRINK);

	m_connections_limit_label 			= Gtk::manage			(new Gtk::Label());
	m_connections_limit_label				->set_markup			("<b>connections limit</b>");
	m_connections_limit 						= Gtk::manage			(new Gtk::Label());
	m_network_table_layout					->attach					(*m_connections_limit_label, 				0, 1,14,15, Gtk::AttachOptions::SHRINK);
	m_network_table_layout					->attach					(*(new Gtk::VSeparator()), 					1, 2,14,15, Gtk::AttachOptions::SHRINK);
	m_network_table_layout					->attach					(*m_connections_limit, 							2, 3,14,15, Gtk::AttachOptions::SHRINK);

	m_error_label 									= Gtk::manage			(new Gtk::Label());
	m_error_label										->set_markup			("<b>error</b>");
	m_error 												= Gtk::manage			(new Gtk::Label("0"));
	m_network_table_layout					->attach					(*m_error_label, 										0, 1,15,16, Gtk::AttachOptions::SHRINK);
	m_network_table_layout					->attach					(*(new Gtk::VSeparator()), 					1, 2,15,16, Gtk::AttachOptions::SHRINK);
	m_network_table_layout					->attach					(*m_error, 													2, 3,15,16, Gtk::AttachOptions::SHRINK);

	m_num_seeds_label 							= Gtk::manage			(new Gtk::Label());
	m_num_seeds_label								->set_markup			("<b>seeds</b>");
	m_num_seeds 										= Gtk::manage			(new Gtk::Label());
	m_peer_table_layout							->attach					(*m_num_seeds_label, 								0, 1, 0, 1, Gtk::AttachOptions::SHRINK);
	m_peer_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2, 0, 1, Gtk::AttachOptions::SHRINK);
	m_peer_table_layout							->attach					(*m_num_seeds, 											2, 3, 0, 1, Gtk::AttachOptions::SHRINK);

	m_num_peers_label 							= Gtk::manage			(new Gtk::Label());
	m_num_peers_label								->set_markup			("<b>peers</b>");
	m_num_peers 										= Gtk::manage			(new Gtk::Label());
	m_peer_table_layout							->attach					(*m_num_peers_label, 								0, 1, 1, 2, Gtk::AttachOptions::SHRINK);
	m_peer_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2, 1, 2, Gtk::AttachOptions::SHRINK);
	m_peer_table_layout							->attach					(*m_num_peers, 											2, 3, 1, 2, Gtk::AttachOptions::SHRINK);

	m_num_complete_label 						= Gtk::manage			(new Gtk::Label());
	m_num_complete_label						->set_markup			("<b>complete</b>");
	m_num_complete 									= Gtk::manage			(new Gtk::Label());
	m_peer_table_layout							->attach					(*m_num_complete_label, 						0, 1, 2, 3, Gtk::AttachOptions::SHRINK);
	m_peer_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2, 2, 3, Gtk::AttachOptions::SHRINK);
	m_peer_table_layout							->attach					(*m_num_complete, 									2, 3, 2, 3, Gtk::AttachOptions::SHRINK);

	m_num_incomplete_label 					= Gtk::manage			(new Gtk::Label());
	m_num_incomplete_label					->set_markup			("<b>incomplete</b>");
	m_num_incomplete 								= Gtk::manage			(new Gtk::Label());
	m_peer_table_layout							->attach					(*m_num_incomplete_label, 					0, 1, 3, 4, Gtk::AttachOptions::SHRINK);
	m_peer_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2, 3, 4, Gtk::AttachOptions::SHRINK);
	m_peer_table_layout							->attach					(*m_num_incomplete, 								2, 3, 3, 4, Gtk::AttachOptions::SHRINK);

	m_connect_candidates_label 			= Gtk::manage			(new Gtk::Label());
	m_connect_candidates_label			->set_markup			("<b>connect candidates</b>");
	m_connect_candidates 						= Gtk::manage			(new Gtk::Label());
	m_peer_table_layout							->attach					(*m_connect_candidates_label, 			0, 1, 4, 5, Gtk::AttachOptions::SHRINK);
	m_peer_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2, 4, 5, Gtk::AttachOptions::SHRINK);
	m_peer_table_layout							->attach					(*m_connect_candidates, 						2, 3, 4, 5, Gtk::AttachOptions::SHRINK);

	m_distributed_full_copies_label	= Gtk::manage			(new Gtk::Label());
	m_distributed_full_copies_label	->set_markup			("<b>distributed full copies</b>");
	m_distributed_full_copies 			= Gtk::manage			(new Gtk::Label());
	m_peer_table_layout							->attach					(*m_distributed_full_copies_label, 	0, 1, 5, 6, Gtk::AttachOptions::SHRINK);
	m_peer_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2, 5, 6, Gtk::AttachOptions::SHRINK);
	m_peer_table_layout							->attach					(*m_distributed_full_copies, 				2, 3, 5, 6, Gtk::AttachOptions::SHRINK);

	m_distributed_fraction_label 		= Gtk::manage			(new Gtk::Label());
	m_distributed_fraction_label		->set_markup			("<b>distributed fraction</b>");
	m_distributed_fraction 					= Gtk::manage			(new Gtk::Label());
	m_peer_table_layout							->attach					(*m_distributed_fraction_label, 		0, 1, 6, 7, Gtk::AttachOptions::SHRINK);
	m_peer_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2, 6, 7, Gtk::AttachOptions::SHRINK);
	m_peer_table_layout							->attach					(*m_distributed_fraction, 					2, 3, 6, 7, Gtk::AttachOptions::SHRINK);

	m_distributed_copies_label 			= Gtk::manage			(new Gtk::Label());
	m_distributed_copies_label			->set_markup			("<b>distributed copies</b>");
	m_distributed_copies 						= Gtk::manage			(new Gtk::Label());
	m_peer_table_layout							->attach					(*m_distributed_copies_label, 			0, 1, 7, 8, Gtk::AttachOptions::SHRINK);
	m_peer_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2, 7, 8, Gtk::AttachOptions::SHRINK);
	m_peer_table_layout							->attach					(*m_distributed_copies, 						2, 3, 7, 8, Gtk::AttachOptions::SHRINK);

	m_paused_label 									= Gtk::manage			(new Gtk::Label());
	m_paused_label									->set_markup			("<b>paused</b>");
	m_paused 												= Gtk::manage			(new Gtk::Label());
	m_bool_table_layout							->attach					(*m_paused_label, 									0, 1, 0, 1, Gtk::AttachOptions::SHRINK);
	m_bool_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2, 0, 1, Gtk::AttachOptions::SHRINK);
	m_bool_table_layout							->attach					(*m_paused, 												2, 3, 0, 1, Gtk::AttachOptions::SHRINK);

	m_is_finished_label 						= Gtk::manage			(new Gtk::Label());
	m_is_finished_label							->set_markup			("<b>is finished</b>");
	m_is_finished 									= Gtk::manage			(new Gtk::Label());
	m_bool_table_layout							->attach					(*m_is_finished_label, 							0, 1, 1, 2, Gtk::AttachOptions::SHRINK);
	m_bool_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2, 1, 2, Gtk::AttachOptions::SHRINK);
	m_bool_table_layout							->attach					(*m_is_finished, 										2, 3, 1, 2, Gtk::AttachOptions::SHRINK);

	m_is_seeding_label 							= Gtk::manage			(new Gtk::Label());
	m_is_seeding_label							->set_markup			("<b>is seeding</b>");
	m_is_seeding 										= Gtk::manage			(new Gtk::Label());
	m_bool_table_layout							->attach					(*m_is_seeding_label, 							0, 1, 2, 3, Gtk::AttachOptions::SHRINK);
	m_bool_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2, 2, 3, Gtk::AttachOptions::SHRINK);
	m_bool_table_layout							->attach					(*m_is_seeding, 										2, 3, 2, 3, Gtk::AttachOptions::SHRINK);

	m_seed_mode_label 							= Gtk::manage			(new Gtk::Label());
	m_seed_mode_label								->set_markup			("<b>seed mode</b>");
	m_seed_mode 										= Gtk::manage			(new Gtk::Label());
	m_bool_table_layout							->attach					(*m_seed_mode_label, 								0, 1, 3, 4, Gtk::AttachOptions::SHRINK);
	m_bool_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2, 3, 4, Gtk::AttachOptions::SHRINK);
	m_bool_table_layout							->attach					(*m_seed_mode, 											2, 3, 3, 4, Gtk::AttachOptions::SHRINK);

	m_super_seeding_label 					= Gtk::manage			(new Gtk::Label());
	m_super_seeding_label						->set_markup			("<b>super seeding</b>");
	m_super_seeding 								= Gtk::manage			(new Gtk::Label());
	m_bool_table_layout							->attach					(*m_super_seeding_label, 						0, 1, 4, 5, Gtk::AttachOptions::SHRINK);
	m_bool_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2, 4, 5, Gtk::AttachOptions::SHRINK);
	m_bool_table_layout							->attach					(*m_super_seeding, 									2, 3, 4, 5, Gtk::AttachOptions::SHRINK);

	m_upload_mode_label 						= Gtk::manage			(new Gtk::Label());
	m_upload_mode_label							->set_markup			("<b>upload mode</b>");
	m_upload_mode 									= Gtk::manage			(new Gtk::Label());
	m_bool_table_layout							->attach					(*m_upload_mode_label, 							0, 1, 5, 6, Gtk::AttachOptions::SHRINK);
	m_bool_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2, 5, 6, Gtk::AttachOptions::SHRINK);
	m_bool_table_layout							->attach					(*m_upload_mode, 										2, 3, 5, 6, Gtk::AttachOptions::SHRINK);

	m_share_mode_label 							= Gtk::manage			(new Gtk::Label());
	m_share_mode_label							->set_markup			("<b>share mode</b>");
	m_share_mode 										= Gtk::manage			(new Gtk::Label());
	m_bool_table_layout							->attach					(*m_share_mode_label, 							0, 1, 6, 7, Gtk::AttachOptions::SHRINK);
	m_bool_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2, 6, 7, Gtk::AttachOptions::SHRINK);
	m_bool_table_layout							->attach					(*m_share_mode, 										2, 3, 6, 7, Gtk::AttachOptions::SHRINK);

	m_auto_managed_label 						= Gtk::manage			(new Gtk::Label());
	m_auto_managed_label						->set_markup			("<b>auto managed</b>");
	m_auto_managed 									= Gtk::manage			(new Gtk::Label());
	m_bool_table_layout							->attach					(*m_auto_managed_label, 						0, 1, 7, 8, Gtk::AttachOptions::SHRINK);
	m_bool_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2, 7, 8, Gtk::AttachOptions::SHRINK);
	m_bool_table_layout							->attach					(*m_auto_managed, 									2, 3, 7, 8, Gtk::AttachOptions::SHRINK);

	m_sequential_download_label 		= Gtk::manage			(new Gtk::Label());
	m_sequential_download_label			->set_markup			("<b>sequential download</b>");
	m_sequential_download 					= Gtk::manage			(new Gtk::Label());
	m_bool_table_layout							->attach					(*m_sequential_download_label, 			0, 1, 8, 9, Gtk::AttachOptions::SHRINK);
	m_bool_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2, 8, 9, Gtk::AttachOptions::SHRINK);
	m_bool_table_layout							->attach					(*m_sequential_download, 						2, 3, 8, 9, Gtk::AttachOptions::SHRINK);

	m_ip_filter_applies_label 			= Gtk::manage			(new Gtk::Label());
	m_ip_filter_applies_label				->set_markup			("<b>ip filter applies</b>");
	m_ip_filter_applies 						= Gtk::manage			(new Gtk::Label());
	m_bool_table_layout							->attach					(*m_ip_filter_applies_label, 				0, 1, 9,10, Gtk::AttachOptions::SHRINK);
	m_bool_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2, 9,10, Gtk::AttachOptions::SHRINK);
	m_bool_table_layout							->attach					(*m_ip_filter_applies, 							2, 3, 9,10, Gtk::AttachOptions::SHRINK);

	m_has_metadata_label 						= Gtk::manage			(new Gtk::Label());
	m_has_metadata_label						->set_markup			("<b>has metadata</b>");
	m_has_metadata 									= Gtk::manage			(new Gtk::Label());
	m_bool_table_layout							->attach					(*m_has_metadata_label, 						0, 1,10,11, Gtk::AttachOptions::SHRINK);
	m_bool_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2,10,11, Gtk::AttachOptions::SHRINK);
	m_bool_table_layout							->attach					(*m_has_metadata, 									2, 3,10,11, Gtk::AttachOptions::SHRINK);

	m_has_incoming_label 						= Gtk::manage			(new Gtk::Label());
	m_has_incoming_label						->set_markup			("<b>has incoming</b>");
	m_has_incoming 									= Gtk::manage			(new Gtk::Label());
	m_bool_table_layout							->attach					(*m_has_incoming_label, 						0, 1,11,12, Gtk::AttachOptions::SHRINK);
	m_bool_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2,11,12, Gtk::AttachOptions::SHRINK);
	m_bool_table_layout							->attach					(*m_has_incoming, 									2, 3,11,12, Gtk::AttachOptions::SHRINK);

	m_moving_storage_label 					= Gtk::manage			(new Gtk::Label());
	m_moving_storage_label					->set_markup			("<b>moving storage</b>");
	m_moving_storage 								= Gtk::manage			(new Gtk::Label());
	m_bool_table_layout							->attach					(*m_moving_storage_label, 					0, 1,12,13, Gtk::AttachOptions::SHRINK);
	m_bool_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2,12,13, Gtk::AttachOptions::SHRINK);
	m_bool_table_layout							->attach					(*m_moving_storage, 								2, 3,12,13, Gtk::AttachOptions::SHRINK);

	m_need_save_resume_label 				= Gtk::manage			(new Gtk::Label());
	m_need_save_resume_label				->set_markup			("<b>need save resume</b>");
	m_need_save_resume 							= Gtk::manage			(new Gtk::Label());
	m_bool_table_layout							->attach					(*m_need_save_resume_label, 				0, 1,13,14, Gtk::AttachOptions::SHRINK);
	m_bool_table_layout							->attach					(*(new Gtk::VSeparator()), 					1, 2,13,14, Gtk::AttachOptions::SHRINK);
	m_bool_table_layout							->attach					(*m_need_save_resume, 							2, 3,13,14, Gtk::AttachOptions::SHRINK);

	m_time_box											->pack_start			(*(new Gtk::HSeparator()), 																Gtk::PACK_SHRINK);
	m_time_box											->pack_start			(*m_time_table_layout, 																		Gtk::PACK_SHRINK);
	m_file_box											->pack_start			(*(new Gtk::HSeparator()), 																Gtk::PACK_SHRINK);
	m_file_box											->pack_start			(*m_file_table_layout, 																		Gtk::PACK_SHRINK);
	m_network_box										->pack_start			(*(new Gtk::HSeparator()), 																Gtk::PACK_SHRINK);
	m_network_box										->pack_start			(*m_network_table_layout, 																Gtk::PACK_SHRINK);
	m_peer_box											->pack_start			(*(new Gtk::HSeparator()), 																Gtk::PACK_SHRINK);
	m_peer_box											->pack_start			(*m_peer_table_layout, 																		Gtk::PACK_SHRINK);
	m_bool_box											->pack_start			(*(new Gtk::HSeparator()), 																Gtk::PACK_SHRINK);
	m_bool_box											->pack_start			(*m_bool_table_layout, 																		Gtk::PACK_SHRINK);

	m_notebook											->append_page			(*m_time_box, 																								   	 	"time");
	m_notebook											->append_page			(*m_file_box, 																										 	"file");
	m_notebook											->append_page			(*m_network_box, 																								 "network");
	m_notebook											->append_page			(*m_peer_box, 																										 	"peer");
	m_notebook											->append_page			(*m_bool_box, 																								   	 	"bool");
	m_notebook											->append_page			(*m_graph, 																												 "graph");
	this														->pack_end				(*m_notebook, 															   Gtk::PACK_EXPAND_WIDGET,	 5);
}

/**
* Updates the torrent info bar.
*/
void GtkTorrentInfoBar::updateInfo																														(shared_ptr<gt::Torrent> selected)
{
	vector<shared_ptr<gt::Torrent> 	 > t 																	 = Application::getSingleton()->getCore()->getTorrents();
	bool selectionExists = false;
	unsigned selectedIndex;
	for(unsigned i = 0; i < t.size(); ++i)
	{
		m_graph												->add							(i, (double)t[i]->getUploadRate(), 					(double)t[i]->getDownloadRate());
		if 																							(selected == 																													 t[i])
		{
			selectedIndex = i;
			selectionExists = true;
		}
	}
	if(																																																						selectionExists)
	{
		this->set_visible(true);
		if(t[selectedIndex]						->getHandle()																													 .status().has_metadata)
		{
			m_progress									->setBlocks				(t[selectedIndex]																							->getPieces());
		}
		m_title												->set_text				(t[selectedIndex]																								->getName());
		m_graph												->select																																			 (selectedIndex);
		m_error												->set_text				(t[selectedIndex]																				 ->getErrorString());
		m_eta													->set_text				(t[selectedIndex]																				 	 ->getEtaString());
		m_save_path										->set_text				(t[selectedIndex]																			->getSavePathString());
		m_next_announce								->set_text				(t[selectedIndex]																	->getNextAnnounceString());
		m_announce_interval						->set_text				(t[selectedIndex]															->getAnnounceIntervalString());
		m_current_tracker							->set_text				(t[selectedIndex]																->getCurrentTrackerString());
		m_down_total									->set_text				(t[selectedIndex]															 ->getTotalDownloadedString());
		m_up_total										->set_text				(t[selectedIndex]																 ->getTotalUploadedString());
		m_total_payload_download			->set_text				(t[selectedIndex]													->getTotalPayloadDownloadString());
		m_total_payload_upload				->set_text				(t[selectedIndex]														->getTotalPayloadUploadString());
		m_total_failed_bytes					->set_text				(t[selectedIndex]																	 ->getFailedBytesString());
		m_total_redundant_bytes				->set_text				(t[selectedIndex]																->getRedundantBytesString());
		m_total_done									->set_text				(t[selectedIndex]																		 ->getTotalDoneString());
		m_total_wanted_done						->set_text				(t[selectedIndex]																		->getWantedDoneString());
		m_total_wanted								->set_text				(t[selectedIndex]																	 ->getTotalWantedString());
		m_all_time_upload							->set_text				(t[selectedIndex]																 ->getAllTimeUploadString());
		m_all_time_download						->set_text				(t[selectedIndex]															 ->getAllTimeDownloadString());
		m_added_time									->set_text				(t[selectedIndex]														 				 ->getAddedTimeString());
		m_completed_time							->set_text				(t[selectedIndex]																 ->getCompletedTimeString());
		m_last_seen_complete					->set_text				(t[selectedIndex]															->getLastSeenCompleteString());
		m_progress_ppm								->set_text				(t[selectedIndex]																	 ->getProgressPpmString());
		m_queue_position							->set_text				(t[selectedIndex]																 ->getQueuePositionString());
		m_download_rate								->set_text				(t[selectedIndex]																	->getDownloadRateString());
		m_upload_rate									->set_text				(t[selectedIndex]																		->getUploadRateString());
		m_download_payload_rate				->set_text				(t[selectedIndex]													 ->getDownloadPayloadRateString());
		m_upload_payload_rate					->set_text				(t[selectedIndex]														 ->getUploadPayloadRateString());
		m_num_seeds										->set_text				(t[selectedIndex]																			->getNumSeedsString());
		m_num_peers										->set_text				(t[selectedIndex]																			->getNumPeersString());
		m_num_complete								->set_text				(t[selectedIndex]																	 ->getNumCompleteString());
		m_num_incomplete							->set_text				(t[selectedIndex]																 ->getNumIncompleteString());
		m_connect_candidates					->set_text				(t[selectedIndex]														 ->getConnectCandidatesString());
		m_num_pieces									->set_text				(t[selectedIndex]																		 ->getNumPiecesString());
		m_distributed_full_copies			->set_text				(t[selectedIndex]												 ->getDistributedFullCopiesString());
		m_distributed_fraction				->set_text				(t[selectedIndex]													 ->getDistributedFractionString());
		m_distributed_copies					->set_text				(t[selectedIndex]														 ->getDistributedCopiesString());
		m_block_size									->set_text				(t[selectedIndex]																		 ->getBlockSizeString());
		m_num_uploads									->set_text				(t[selectedIndex]																		->getNumUploadsString());
		m_num_connections  						->set_text				(t[selectedIndex]																->getNumConnectionsString());
		m_uploads_limit								->set_text				(t[selectedIndex]																	->getUploadsLimitString());
		m_connections_limit						->set_text				(t[selectedIndex]															->getConnectionsLimitString());
		m_up_bandwidth_queue					->set_text				(t[selectedIndex]															->getUpBandwidthQueueString());
		m_down_bandwidth_queue				->set_text				(t[selectedIndex]														->getDownBandwidthQueueString());
		m_time_since_upload						->set_text				(t[selectedIndex]															 ->getTimeSinceUploadString());
		m_time_since_download					->set_text				(t[selectedIndex]														 ->getTimeSinceDownloadString());
		m_active_time									->set_text				(t[selectedIndex]																		->getActiveTimeString());
		m_finished_time								->set_text				(t[selectedIndex]																	->getFinishedTimeString());
		m_seeding_time								->set_text				(t[selectedIndex]																	 ->getSeedingTimeString());
		m_seed_rank										->set_text				(t[selectedIndex]																			->getSeedRankString());
		m_last_scrape									->set_text				(t[selectedIndex]																		->getLastScrapeString());
		m_priority 										->set_text				(t[selectedIndex]																			->getPriorityString());
		m_state 											->set_text				(t[selectedIndex]																				 ->getStateString());
		m_need_save_resume						->set_text				(t[selectedIndex]																->getNeedSaveResumeString());
		m_ip_filter_applies						->set_text				(t[selectedIndex]															 ->getIpFilterAppliesString());
		m_upload_mode									->set_text				(t[selectedIndex]																		->getUploadModeString());
		m_share_mode									->set_text				(t[selectedIndex]																		 ->getShareModeString());
		m_super_seeding								->set_text				(t[selectedIndex]																	->getSuperSeedingString());
		m_paused											->set_text				(t[selectedIndex]																				->getPausedString());
		m_auto_managed								->set_text				(t[selectedIndex]																	 ->getAutoManagedString());
		m_sequential_download					->set_text				(t[selectedIndex]														->getSequentialDownloadString());
		m_is_seeding									->set_text				(t[selectedIndex]																		 ->getIsSeedingString());
		m_is_finished									->set_text				(t[selectedIndex]																		->getIsFinishedString());
		m_has_metadata								->set_text				(t[selectedIndex]																	 ->getHasMetadataString());
		m_has_incoming								->set_text				(t[selectedIndex]																	 ->getHasIncomingString());
		m_seed_mode										->set_text				(t[selectedIndex]																			->getSeedModeString());
		m_moving_storage							->set_text				(t[selectedIndex]																 ->getMovingStorageString());
		m_info_hash										->set_text				(t[selectedIndex]																			->getInfoHashString());
	}
	else
	{
		this->set_visible(false);
	}
}
