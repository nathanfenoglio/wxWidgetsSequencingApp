#pragma once
#include "wx/wx.h"

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

private:
	wxStaticText* input_label_1;
	wxTextCtrl* input_box_1;

	wxButton* mv_seq_1_to_hold_this_1;
	wxButton* mv_seq_1_to_hold_this_2;

	wxStaticText* seq_1_param_1_label;
	wxTextCtrl* seq_1_param_1_box;

	wxStaticText* seq_1_param_2_label;
	wxTextCtrl* seq_1_param_2_box;

	wxStaticText* seq_2_param_1_label;
	wxTextCtrl* seq_2_param_1_box;

	wxStaticText* seq_2_param_2_label;
	wxTextCtrl* seq_2_param_2_box;

	wxStaticText* seq_1_sum_inv_num_label;
	wxTextCtrl* seq_1_sum_inv_num_box;

	wxStaticText* seq_2_sum_inv_num_label;
	wxTextCtrl* seq_2_sum_inv_num_box;

	wxStaticText* seq_1_tower_of_hanoi_label;
	wxTextCtrl* seq_1_tower_of_hanoi_box;

	wxStaticText* seq_2_tower_of_hanoi_label;
	wxTextCtrl* seq_2_tower_of_hanoi_box;

	wxStaticText* input_label_2;
	wxTextCtrl* input_box_2;

	wxButton* mv_seq_2_to_hold_this_1;
	wxButton* mv_seq_2_to_hold_this_2;

	wxStaticText* replace_this_label;
	wxTextCtrl* replace_this_input_box;

	wxStaticText* replace_with_label;
	wxTextCtrl* replace_with_input_box;

	wxStaticText* output_label_1;
	wxTextCtrl* output_box_1;
	
	wxStaticText* seq_1_scalar_label;
	wxTextCtrl* seq_1_scalar_box;
	wxStaticText* seq_2_scalar_label;
	wxTextCtrl* seq_2_scalar_box;
	wxStaticText* mod_by_label;
	wxTextCtrl* mod_by_box;

	wxButton* mv_out_to_seq_1;
	wxButton* mv_out_to_seq_2;

	wxStaticText* hold_this_label_1;
	wxTextCtrl* hold_this_box_1;
	wxStaticText* hold_this_label_2;
	wxTextCtrl* hold_this_box_2;

	wxButton* mv_out_to_hold_this_1;
	wxButton* mv_out_to_hold_this_2;

	wxButton* repl_seq_1_btn;
	wxButton* repl_seq_2_btn;

	wxButton* splice_btn;

	wxButton* modby_addby_btn;
	wxButton* modby_addby_btn_2;
	
	wxButton* addby_modby_btn;
	wxButton* addby_modby_btn_2;

	wxButton* mult_seqs_by_scalars_add_together_mod_btn;

	wxButton* rot_seq_1_left_btn;
	wxButton* rot_seq_1_right_btn;

	wxButton* rot_seq_2_left_btn;
	wxButton* rot_seq_2_right_btn;
	
	wxButton* reverse_seq_1_btn;
	wxButton* reverse_seq_2_btn;

	wxButton* repl_an_int_with_a_str_seq_1_btn;
	wxButton* repl_an_int_with_a_str_seq_2_btn;

	wxButton* seq_1_sum_inv_button;
	wxButton* seq_2_sum_inv_button;

	wxButton* seq_1_tower_of_hanoi;
	wxButton* seq_2_tower_of_hanoi;

public:
	void OnSpliceButtonClicked(wxCommandEvent& evt); //event handler functions
	void OnReplSeq1ButtonClicked(wxCommandEvent& evt);
	void OnReplSeq2ButtonClicked(wxCommandEvent& evt);
	void OnMvOutToSeq1ButtonClicked(wxCommandEvent& evt);
	void OnMvOutToSeq2ButtonClicked(wxCommandEvent& evt);
	void OnSeq1ModByAddByButtonClicked(wxCommandEvent& evt);
	void OnSeq2ModByAddByButtonClicked(wxCommandEvent& evt);
	void OnSeq1AddByModByButtonClicked(wxCommandEvent& evt);
	void OnSeq2AddByModByButtonClicked(wxCommandEvent& evt);
	void OnMultSeqsByScalarsAddTogetherModButtonClicked(wxCommandEvent& evt);
	void OnSeq1RotateLeftButtonClicked(wxCommandEvent& evt);
	void OnSeq1RotateRightButtonClicked(wxCommandEvent& evt);
	void OnSeq2RotateLeftButtonClicked(wxCommandEvent& evt);
	void OnSeq2RotateRightButtonClicked(wxCommandEvent& evt);
	void OnSeq1ReverseButtonClicked(wxCommandEvent& evt);
	void OnSeq2ReverseButtonClicked(wxCommandEvent& evt);
	void OnSeq1ReplaceAnIntWithAStrButtonClicked(wxCommandEvent& evt);
	void OnSeq2ReplaceAnIntWithAStrButtonClicked(wxCommandEvent& evt);
	void OnSeq1SumInversionButtonClicked(wxCommandEvent& evt);
	void OnSeq2SumInversionButtonClicked(wxCommandEvent& evt);
	void OnSeq1TowerOfHanoiButtonClicked(wxCommandEvent& evt);
	void OnSeq2TowerOfHanoiButtonClicked(wxCommandEvent& evt);
	void OnMvOutToHoldThis1ButtonClicked(wxCommandEvent& evt);
	void OnMvOutToHoldThis2ButtonClicked(wxCommandEvent& evt);
	void OnMvSeq1ToHoldThis1ButtonClicked(wxCommandEvent& evt);
	void OnMvSeq1ToHoldThis2ButtonClicked(wxCommandEvent& evt);
	void OnMvSeq2ToHoldThis1ButtonClicked(wxCommandEvent& evt);
	void OnMvSeq2ToHoldThis2ButtonClicked(wxCommandEvent& evt);

	template <class flam>
	std::string whatev_to_string(std::vector <flam> incoming_vect, bool keep_commas);
	std::vector <int> comma_sep_str_to_int_vector(std::string str);
	std::vector <int> multiple_vectors_to_one_vector_one_element_by_one_element(std::vector < std::vector <int> > all_vectors);
	std::vector <int> mod_all_vector_by_certain_amount_and_add_by_certain_amount(std::vector <int> the_vector, int mod_by, int add_to, bool add_first);	
	std::vector <int> add_two_vectors_ability_to_mult_by_scalars_too(std::vector <int> vect_a, int scalar_a, std::vector <int> vect_b, int scalar_b, int mod_by);
	std::vector <int> sum_inversion(std::vector <int> orig_seq, int sum_whatev);
	
	class Tower_Of_Hanoi{
	public:

		int num_discs;
		//represent with 2D list containing the order of the discs in each of the possible pole spaces
	    std::vector < std::vector <int> > discs_on_poles;
	    //just saving all of the states of the discs on poles in giant array to use
	    std::vector < std::vector < std::vector <int> > > discs_on_poles_in_time;
		
		template <class T>
		T pop_and_return(std::vector <T> &vect);
		template <class T>
		T pop_front_and_return(std::vector <T> &vect);
		std::vector <int> multiple_vectors_to_one_vector_one_element_by_one_element(std::vector < std::vector <int> > all_vectors_one_time, std::vector <int> scale_to_translate_to);
		
		void move(int f, int t); //f - from, t - to
		void hanoi(int n, int f, int h, int t); //n - # of discs, f - from, h - helper pole (go between), t - to

	};
	
	wxDECLARE_EVENT_TABLE(); //macro to get event table to be able to listen and handle stuff I guess

};

