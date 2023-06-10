//have installer created and able to be downloaded at 
//https://app.box.com/s/xfcio6glciu63e0uqhwhqmjvi1tb092r

#include "cMain.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <regex>

//macro to start event table listening for events takes class that it is producing the events for and the base class
wxBEGIN_EVENT_TABLE(cMain, wxFrame)

//id of the button (make the same as id when instantiating the button) and the function that will handle the button being pressed
EVT_BUTTON(10001, OnSpliceButtonClicked)
EVT_BUTTON(10002, OnReplSeq1ButtonClicked)
EVT_BUTTON(10003, OnReplSeq2ButtonClicked)
//YOU DID HAVE 10004 AND 10005 BELOW, BUT THOSE DIDN'T WORK
//SHOULD TO THE HIGHEST THING GOING FORWARD
EVT_BUTTON(wxID_HIGHEST+1, OnMvOutToSeq1ButtonClicked)
EVT_BUTTON(wxID_HIGHEST+2, OnMvOutToSeq2ButtonClicked)
EVT_BUTTON(wxID_HIGHEST+3, OnSeq1ModByAddByButtonClicked)
EVT_BUTTON(wxID_HIGHEST+4, OnSeq2ModByAddByButtonClicked)
EVT_BUTTON(wxID_HIGHEST+5, OnSeq1AddByModByButtonClicked)
EVT_BUTTON(wxID_HIGHEST+6, OnSeq2AddByModByButtonClicked)
EVT_BUTTON(wxID_HIGHEST+7, OnMultSeqsByScalarsAddTogetherModButtonClicked)
EVT_BUTTON(wxID_HIGHEST+8, OnSeq1RotateLeftButtonClicked)
EVT_BUTTON(wxID_HIGHEST+9, OnSeq1RotateRightButtonClicked)
EVT_BUTTON(wxID_HIGHEST+10, OnSeq2RotateLeftButtonClicked)
EVT_BUTTON(wxID_HIGHEST+11, OnSeq2RotateRightButtonClicked)
EVT_BUTTON(wxID_HIGHEST+12, OnSeq1ReverseButtonClicked)
EVT_BUTTON(wxID_HIGHEST+13, OnSeq2ReverseButtonClicked)
EVT_BUTTON(wxID_HIGHEST+14, OnSeq1ReplaceAnIntWithAStrButtonClicked)
EVT_BUTTON(wxID_HIGHEST+15, OnSeq2ReplaceAnIntWithAStrButtonClicked)
EVT_BUTTON(wxID_HIGHEST+16, OnSeq1SumInversionButtonClicked)
EVT_BUTTON(wxID_HIGHEST+17, OnSeq2SumInversionButtonClicked)
EVT_BUTTON(wxID_HIGHEST+18, OnSeq1TowerOfHanoiButtonClicked)
EVT_BUTTON(wxID_HIGHEST+19, OnSeq2TowerOfHanoiButtonClicked)
EVT_BUTTON(wxID_HIGHEST+20, OnMvOutToHoldThis1ButtonClicked)
EVT_BUTTON(wxID_HIGHEST+21, OnMvOutToHoldThis2ButtonClicked)
EVT_BUTTON(wxID_HIGHEST+22, OnMvSeq1ToHoldThis1ButtonClicked)
EVT_BUTTON(wxID_HIGHEST+23, OnMvSeq1ToHoldThis2ButtonClicked)
EVT_BUTTON(wxID_HIGHEST+24, OnMvSeq2ToHoldThis1ButtonClicked)
EVT_BUTTON(wxID_HIGHEST+25, OnMvSeq2ToHoldThis2ButtonClicked)

wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Take 2 Sequences And Do A Bunch Of Stuff", wxPoint(30, 30), wxSize(900, 900)) {
	wxPanel* panel = new wxPanel(this, wxID_ANY);
	panel->SetBackgroundColour(wxColor(0, 255, 255));	

	wxBoxSizer* outer_box = new wxBoxSizer(wxVERTICAL); //what all of the other sizers will go in

	//sequence 1 input box
	wxBoxSizer* hbox1 = new wxBoxSizer(wxHORIZONTAL);
	input_label_1 = new wxStaticText(panel, wxID_ANY, wxT("sequence 1: ", wxDefaultPosition, wxSize(70, -1)));
	hbox1->Add(input_label_1, 0, wxRIGHT, 10);
	input_box_1 = new wxTextCtrl(panel, wxID_ANY);
	hbox1->Add(input_box_1, 1);
	outer_box->Add(hbox1, 0, wxEXPAND | wxLEFT | wxTOP | wxRIGHT, 30);

	//sequence 1 move to hold this buttons
	wxBoxSizer* h_seq_1_move_btns_box = new wxBoxSizer(wxHORIZONTAL);
	mv_seq_1_to_hold_this_1 = new wxButton(panel, wxID_HIGHEST+22, "move to hold 1");
	h_seq_1_move_btns_box->Add(mv_seq_1_to_hold_this_1, 0, wxRIGHT, 10);
	mv_seq_1_to_hold_this_2 = new wxButton(panel, wxID_HIGHEST+23, "move to hold 2");
	h_seq_1_move_btns_box->Add(mv_seq_1_to_hold_this_2, 0, wxRIGHT, 10);

	outer_box->Add(h_seq_1_move_btns_box, 0, wxALIGN_CENTER | wxTOP, 10);

	//sequence 1 specific parameter boxes
	wxBoxSizer* h_seq_1_params_box = new wxBoxSizer(wxHORIZONTAL);
	seq_1_param_1_label = new wxStaticText(panel, wxID_ANY, wxT("mod by: "), wxDefaultPosition, wxSize(70, -1));
	h_seq_1_params_box->Add(seq_1_param_1_label, 0);
	seq_1_param_1_box = new wxTextCtrl(panel, wxID_ANY);
	h_seq_1_params_box->Add(seq_1_param_1_box, 0, wxRIGHT, 20);

	seq_1_param_2_label = new wxStaticText(panel, wxID_ANY, wxT("add by: "), wxDefaultPosition, wxSize(70, -1));
	h_seq_1_params_box->Add(seq_1_param_2_label, 0);
	seq_1_param_2_box = new wxTextCtrl(panel, wxID_ANY);
	h_seq_1_params_box->Add(seq_1_param_2_box, 0, wxRIGHT, 20);

	seq_1_sum_inv_num_label = new wxStaticText(panel, wxID_ANY, wxT("sum\ninversion #: "), wxDefaultPosition, wxSize(70, -1));
	h_seq_1_params_box->Add(seq_1_sum_inv_num_label, 0);
	seq_1_sum_inv_num_box = new wxTextCtrl(panel, wxID_ANY);
	h_seq_1_params_box->Add(seq_1_sum_inv_num_box, 0, wxRIGHT, 20);

	seq_1_tower_of_hanoi_label = new wxStaticText(panel, wxID_ANY, wxT("# discs\nt_o_h: "), wxDefaultPosition, wxSize(70, -1));
	h_seq_1_params_box->Add(seq_1_tower_of_hanoi_label, 0);
	seq_1_tower_of_hanoi_box = new wxTextCtrl(panel, wxID_ANY);
	h_seq_1_params_box->Add(seq_1_tower_of_hanoi_box, 0, wxRIGHT, 20);

	outer_box->Add(h_seq_1_params_box, 0, wxALIGN_CENTER | wxBOTTOM | wxTOP, 10);

	//mod by a value, then add by a value button
	wxBoxSizer* h_seq_1_specific_btns = new wxBoxSizer(wxHORIZONTAL);
	modby_addby_btn = new wxButton(panel, wxID_HIGHEST+3, "Mod By Add By");
	h_seq_1_specific_btns->Add(modby_addby_btn, 0, wxRIGHT, 10);

	//add a value, then mod by a value sequence 1
	addby_modby_btn = new wxButton(panel, wxID_HIGHEST+5, "Add By Mod By");
	h_seq_1_specific_btns->Add(addby_modby_btn, 0, wxRIGHT, 10);

	//rotate sequence 1 to the left
	rot_seq_1_left_btn = new wxButton(panel, wxID_HIGHEST+8, "Rotate Left");
	h_seq_1_specific_btns->Add(rot_seq_1_left_btn, 0, wxRIGHT, 10);

	//rotate sequence 1 to the right
	rot_seq_1_right_btn = new wxButton(panel, wxID_HIGHEST+9, "Rotate Right");
	h_seq_1_specific_btns->Add(rot_seq_1_right_btn, 0, wxRIGHT, 10);

	//reverse sequence 1
	reverse_seq_1_btn = new wxButton(panel, wxID_HIGHEST+12, "Reverse");
	h_seq_1_specific_btns->Add(reverse_seq_1_btn, 0, wxRIGHT, 10);

	//sum inversion sequence 1
	seq_1_sum_inv_button = new wxButton(panel, wxID_HIGHEST+16, "Sum Inversion");
	h_seq_1_specific_btns->Add(seq_1_sum_inv_button, 0, wxRIGHT, 10);

	//tower of hanoi sequence 1
	seq_1_tower_of_hanoi = new wxButton(panel, wxID_HIGHEST+18, "Tower of Hanoi It");
	h_seq_1_specific_btns->Add(seq_1_tower_of_hanoi, 0, wxRIGHT, 10);

	outer_box->Add(h_seq_1_specific_btns, 0, wxALIGN_CENTER | wxBOTTOM, 50);

//*********************************************************************************
	//sequence 2 input box
	wxBoxSizer* hbox2 = new wxBoxSizer(wxHORIZONTAL);
	input_label_2 = new wxStaticText(panel, wxID_ANY, wxT("sequence 2: ", wxDefaultPosition, wxSize(70, -1)));
	hbox2->Add(input_label_2, 0, wxRIGHT, 10);
	input_box_2 = new wxTextCtrl(panel, wxID_ANY);
	hbox2->Add(input_box_2, 1, wxRIGHT, 10);
	outer_box->Add(hbox2, 0, wxEXPAND | wxLEFT | wxRIGHT, 30);

	//sequence 2 move to hold this buttons
	wxBoxSizer* h_seq_2_move_btns_box = new wxBoxSizer(wxHORIZONTAL);
	mv_seq_2_to_hold_this_1 = new wxButton(panel, wxID_HIGHEST+24, "move to hold 1");
	h_seq_2_move_btns_box->Add(mv_seq_2_to_hold_this_1, 0, wxRIGHT, 10);
	mv_seq_2_to_hold_this_2 = new wxButton(panel, wxID_HIGHEST+25, "move to hold 2");
	h_seq_2_move_btns_box->Add(mv_seq_2_to_hold_this_2, 0, wxRIGHT, 10);

	outer_box->Add(h_seq_2_move_btns_box, 0, wxALIGN_CENTER | wxTOP, 10);

	//sequence 2 specific parameter boxes
	wxBoxSizer* h_seq_2_params_box = new wxBoxSizer(wxHORIZONTAL);
	seq_2_param_1_label = new wxStaticText(panel, wxID_ANY, wxT("mod by: "), wxDefaultPosition, wxSize(70, -1));
	h_seq_2_params_box->Add(seq_2_param_1_label, 0);
	seq_2_param_1_box = new wxTextCtrl(panel, wxID_ANY);
	h_seq_2_params_box->Add(seq_2_param_1_box, 0, wxRIGHT, 20);

	seq_2_param_2_label = new wxStaticText(panel, wxID_ANY, wxT("add by: "), wxDefaultPosition, wxSize(70, -1));
	h_seq_2_params_box->Add(seq_2_param_2_label, 0);
	seq_2_param_2_box = new wxTextCtrl(panel, wxID_ANY);
	h_seq_2_params_box->Add(seq_2_param_2_box, 0, wxRIGHT, 20);

	seq_2_sum_inv_num_label = new wxStaticText(panel, wxID_ANY, wxT("sum\ninversion #: "), wxDefaultPosition, wxSize(70, -1));
	h_seq_2_params_box->Add(seq_2_sum_inv_num_label, 0);
	seq_2_sum_inv_num_box = new wxTextCtrl(panel, wxID_ANY);
	h_seq_2_params_box->Add(seq_2_sum_inv_num_box, 0, wxRIGHT, 20);

	seq_2_tower_of_hanoi_label = new wxStaticText(panel, wxID_ANY, wxT("# discs\nt_o_h: "), wxDefaultPosition, wxSize(70, -1));
	h_seq_2_params_box->Add(seq_2_tower_of_hanoi_label, 0);
	seq_2_tower_of_hanoi_box = new wxTextCtrl(panel, wxID_ANY);
	h_seq_2_params_box->Add(seq_2_tower_of_hanoi_box, 0, wxRIGHT, 20);

	outer_box->Add(h_seq_2_params_box, 0, wxALIGN_CENTER | wxBOTTOM | wxTOP, 10);

	//mod by a value, then add by a value button
	wxBoxSizer* h_seq_2_specific_btns = new wxBoxSizer(wxHORIZONTAL);
	modby_addby_btn_2 = new wxButton(panel, wxID_HIGHEST+4, "Mod By Add By");
	h_seq_2_specific_btns->Add(modby_addby_btn_2, 0, wxRIGHT, 10);

	//add a value, then mod by a value sequence 1
	addby_modby_btn = new wxButton(panel, wxID_HIGHEST+6, "Add By Mod By");
	h_seq_2_specific_btns->Add(addby_modby_btn, 0, wxRIGHT, 10);

	//rotate sequence 2 to the left
	rot_seq_2_left_btn = new wxButton(panel, wxID_HIGHEST+10, "Rotate Left");
	h_seq_2_specific_btns->Add(rot_seq_2_left_btn, 0, wxRIGHT, 10);
	
	//rotate sequence 2 to the right
	rot_seq_2_right_btn = new wxButton(panel, wxID_HIGHEST+11, "Rotate Right");
	h_seq_2_specific_btns->Add(rot_seq_2_right_btn, 0, wxRIGHT, 10);

	//reverse sequence 2
	reverse_seq_2_btn = new wxButton(panel, wxID_HIGHEST+13, "Reverse");
	h_seq_2_specific_btns->Add(reverse_seq_2_btn, 0, wxRIGHT, 10);

	//sum inversion sequence 2
	seq_2_sum_inv_button = new wxButton(panel, wxID_HIGHEST+17, "Sum Inversion");
	h_seq_2_specific_btns->Add(seq_2_sum_inv_button, 0, wxRIGHT, 10);

	//tower of hanoi sequence 2
	seq_2_tower_of_hanoi = new wxButton(panel, wxID_HIGHEST+19, "Tower of Hanoi It");
	h_seq_2_specific_btns->Add(seq_2_tower_of_hanoi, 0, wxRIGHT, 10);
	
	outer_box->Add(h_seq_2_specific_btns, 0, wxALIGN_CENTER | wxBOTTOM, 20);

//*********************************************************************************
	//how about a replace element function 
	//box for what to replace
	wxBoxSizer* h_replace_fields_box = new wxBoxSizer(wxHORIZONTAL);
	replace_this_label = new wxStaticText(panel, wxID_ANY, wxT("replace this: "), wxDefaultPosition, wxSize(70, -1));
	h_replace_fields_box->Add(replace_this_label, 0, wxRIGHT, 10);
	replace_this_input_box = new wxTextCtrl(panel, wxID_ANY);
	h_replace_fields_box->Add(replace_this_input_box, 1, wxRIGHT, 30);
	
	//box for what to replace with
	replace_with_label = new wxStaticText(panel, wxID_ANY, wxT("replace with: "), wxDefaultPosition, wxSize(70, -1));
	h_replace_fields_box->Add(replace_with_label, 0, wxRIGHT, 10);
	replace_with_input_box = new wxTextCtrl(panel, wxID_ANY);
	h_replace_fields_box->Add(replace_with_input_box, 1);

	outer_box->Add(h_replace_fields_box, 0, wxLEFT | wxRIGHT | wxTOP | wxALIGN_CENTER, 30);

	//button for apply to sequence 1
	wxBoxSizer* h_repl_btns_box = new wxBoxSizer(wxHORIZONTAL);
	repl_seq_1_btn = new wxButton(panel, 10002, "apply replacement\nto sequence 1");
	h_repl_btns_box->Add(repl_seq_1_btn, 0, wxRIGHT, 10);

	//button for apply to sequence 2
	repl_seq_2_btn = new wxButton(panel, 10003, "apply replacement\nto sequence 2");
	h_repl_btns_box->Add(repl_seq_2_btn, 0, wxRIGHT, 10);

	//add button to replace whatev substring with a character string
	//for like rests or whatever else
	//I guess as you were doing stuff with the app, wouldn't want to replace until the end
	//could always use a place holder # until you were done messing with the transformation operations in the app
	repl_an_int_with_a_str_seq_1_btn = new wxButton(panel, wxID_HIGHEST+14, "replace with string\nsequence 1");
	h_repl_btns_box->Add(repl_an_int_with_a_str_seq_1_btn, 0, wxRIGHT, 10);

	//replace an int with a string sequence 2
	repl_an_int_with_a_str_seq_2_btn = new wxButton(panel, wxID_HIGHEST+15, "replace with string\nsequence 2");
	h_repl_btns_box->Add(repl_an_int_with_a_str_seq_2_btn, 0, wxRIGHT, 10);

	outer_box->Add(h_repl_btns_box, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 20);

	//splice button
	splice_btn = new wxButton(panel, 10001, "splice sequences\n");
	wxBoxSizer* hbox3 = new wxBoxSizer(wxHORIZONTAL);
	hbox3->Add(splice_btn, 0, wxRIGHT, 10);

	wxBoxSizer* h_misc_both_seq_operations_box = new wxBoxSizer(wxHORIZONTAL);
	seq_1_scalar_label = new wxStaticText(panel, wxID_ANY, wxT("sequence 1\nscalar: "), wxDefaultPosition, wxSize(70, -1));
	h_misc_both_seq_operations_box->Add(seq_1_scalar_label, 0);
	seq_1_scalar_box = new wxTextCtrl(panel, wxID_ANY);
	h_misc_both_seq_operations_box->Add(seq_1_scalar_box, 0, wxRIGHT, 20);

	seq_2_scalar_label = new wxStaticText(panel, wxID_ANY, wxT("sequence 2\nscalar: "), wxDefaultPosition, wxSize(70, -1));
	h_misc_both_seq_operations_box->Add(seq_2_scalar_label, 0);
	seq_2_scalar_box = new wxTextCtrl(panel, wxID_ANY);
	h_misc_both_seq_operations_box->Add(seq_2_scalar_box, 0, wxRIGHT, 20);

	mod_by_label = new wxStaticText(panel, wxID_ANY, wxT("mod by: "), wxDefaultPosition, wxSize(70, -1));
	h_misc_both_seq_operations_box->Add(mod_by_label, 0);
	mod_by_box = new wxTextCtrl(panel, wxID_ANY);
	h_misc_both_seq_operations_box->Add(mod_by_box, 0, wxRIGHT, 20);

	outer_box->Add(h_misc_both_seq_operations_box, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);

	//multiply each sequence by scalar, add sequences, and mod button
	mult_seqs_by_scalars_add_together_mod_btn = new wxButton(panel, wxID_HIGHEST+7, "multiply sequences by scalars\nadd together mod by");
	hbox3->Add(mult_seqs_by_scalars_add_together_mod_btn, 0, wxRIGHT, 10);

	outer_box->Add(hbox3, 0, wxALIGN_CENTER);

	//output box
	wxBoxSizer* hbox4 = new wxBoxSizer(wxHORIZONTAL);
	output_label_1 = new wxStaticText(panel, wxID_ANY, wxT("output: ", wxDefaultPosition, wxSize(70, -1)));
	hbox4->Add(output_label_1, 0, wxRIGHT, 10);
	output_box_1 = new wxTextCtrl(panel, wxID_ANY);
	hbox4->Add(output_box_1, 1);
	outer_box->Add(hbox4, 0, wxEXPAND | wxRIGHT | wxTOP | wxLEFT, 30);

	//move output to sequence 1
	wxBoxSizer* h_move_output_to_input_btns_box = new wxBoxSizer(wxHORIZONTAL);
	mv_out_to_seq_1 = new wxButton(panel, wxID_HIGHEST+1, "move to\nsequence 1");
	h_move_output_to_input_btns_box->Add(mv_out_to_seq_1, 0, wxRIGHT, 10);
	//move output to sequence 2
	mv_out_to_seq_2 = new wxButton(panel, wxID_HIGHEST+2, "move to\nsequence 2");
	h_move_output_to_input_btns_box->Add(mv_out_to_seq_2, 0, wxRIGHT, 10);

	//move output to hold this for a sec box 1
	mv_out_to_hold_this_1 = new wxButton(panel, wxID_HIGHEST+20, "move to\nhold 1");
	h_move_output_to_input_btns_box->Add(mv_out_to_hold_this_1, 0, wxRIGHT, 10);
	//move output to hold this for a sec box 1
	mv_out_to_hold_this_2 = new wxButton(panel, wxID_HIGHEST+21, "move to\nhold 2");
	h_move_output_to_input_btns_box->Add(mv_out_to_hold_this_2, 0, wxRIGHT, 10);

	outer_box->Add(h_move_output_to_input_btns_box, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);

	//hold this for a sec box 1
	wxBoxSizer* hbox5 = new wxBoxSizer(wxHORIZONTAL); 
	hold_this_label_1 = new wxStaticText(panel, wxID_ANY, wxT("hold this for a sec 1: ", wxDefaultPosition, wxSize(70, -1)));
	hbox5->Add(hold_this_label_1, 0, wxRIGHT, 10);
	hold_this_box_1 = new wxTextCtrl(panel, wxID_ANY);
	hbox5->Add(hold_this_box_1, 1);
	outer_box->Add(hbox5, 0, wxEXPAND | wxALL, 10);

	//hold this for a sec box 1
	wxBoxSizer* hbox6 = new wxBoxSizer(wxHORIZONTAL); 
	hold_this_label_2 = new wxStaticText(panel, wxID_ANY, wxT("hold this for a sec 2: ", wxDefaultPosition, wxSize(70, -1)));
	hbox6->Add(hold_this_label_2, 0, wxRIGHT, 10);
	hold_this_box_2 = new wxTextCtrl(panel, wxID_ANY);
	hbox6->Add(hold_this_box_2, 1);
	outer_box->Add(hbox6, 0, wxEXPAND | wxALL, 10);

	panel->SetSizer(outer_box);
	Centre();
}

cMain::~cMain() {

}

void cMain::OnSpliceButtonClicked(wxCommandEvent& evt) {
	try{

		std::string txt_from_box = std::string(input_box_1->GetValue());
		std::string txt_from_box_2 = std::string(input_box_2->GetValue());

		//get a comma separated list of ints from the text box and put it in a vector
		std::vector <int> ints_in_a_vector = comma_sep_str_to_int_vector(txt_from_box);
		std::vector <int> ints_in_a_vector_2 = comma_sep_str_to_int_vector(txt_from_box_2);
		std::vector < std::vector <int> > both_vectors;
		both_vectors.push_back(ints_in_a_vector);
		both_vectors.push_back(ints_in_a_vector_2);
		
		std::string str_to_print = whatev_to_string(multiple_vectors_to_one_vector_one_element_by_one_element(both_vectors), true);

		output_box_1->ChangeValue(str_to_print);

		evt.Skip();
	}
	catch(...){
		std::cout << "exception, you did something wrong" << std::endl;
	}
}

void cMain::OnReplSeq1ButtonClicked(wxCommandEvent& evt){
	try{

		std::vector <int> changed_vector;
		
		//get text from input_box_1 and put in a vector of ints
		std::string seq_1_txt = std::string(input_box_1->GetValue());
		std::vector <int> seq_1_vector = comma_sep_str_to_int_vector(seq_1_txt);

		//put ints in vectors	
		std::string repl_this_txt = std::string(replace_this_input_box->GetValue());
		std::string repl_with_txt = std::string(replace_with_input_box->GetValue());
		std::vector <int> repl_this_vector = comma_sep_str_to_int_vector(repl_this_txt);
		std::vector <int> repl_with_vector = comma_sep_str_to_int_vector(repl_with_txt);

		//instead of just replacing one thing with one thing
		//search for however many matches are in repl_this_vector
		//if there is a match in the original vector for all of repl_this_vector
		//then add everything from repl_with_vector in that spot
		for(int i = 0; i < seq_1_vector.size(); i++){
			bool all_match = true;
			//check if there is enough left in original vector to even match up with repl_this_vector
			if((seq_1_vector.size() - i) < repl_this_vector.size()){
				all_match = false;
			}
			else{ //enough elements to check so check for match
				for(int j = 0; j < repl_this_vector.size(); j++){
					if(seq_1_vector[i + j] != repl_this_vector[j]){
						all_match = false;
						break;
					}
				}
			}

			if(all_match){
				for(int j = 0; j < repl_with_vector.size(); j++){
					changed_vector.push_back(repl_with_vector[j]);
				}
				//need to skip as many spots in original vector as repl_this_vector.size()
				i = i + repl_this_vector.size() - 1; 
			}
			else{
				changed_vector.push_back(seq_1_vector[i]);
			}
		}

		std::string str_to_print = whatev_to_string(changed_vector, true);
		input_box_1->ChangeValue(str_to_print);
		
		evt.Skip();
	}
	catch(...){
		std::cout << "exception, you did something wrong" << std::endl;
	}
}

void cMain::OnReplSeq2ButtonClicked(wxCommandEvent& evt){
	try{

		std::vector <int> changed_vector;

		//get text from input_box_1 and put in a vector of ints
		std::string seq_2_txt = std::string(input_box_2->GetValue());
		std::vector <int> seq_2_vector = comma_sep_str_to_int_vector(seq_2_txt);

		//put ints in vectors	
		std::string repl_this_txt = std::string(replace_this_input_box->GetValue());
		std::string repl_with_txt = std::string(replace_with_input_box->GetValue());
		std::vector <int> repl_this_vector = comma_sep_str_to_int_vector(repl_this_txt);
		std::vector <int> repl_with_vector = comma_sep_str_to_int_vector(repl_with_txt);

		//instead of just replacing one thing with one thing
		//search for however many matches are in repl_this_vector
		//if there is a match in the original vector for all of repl_this_vector
		//then add everything from repl_with_vector in that spot
		for(int i = 0; i < seq_2_vector.size(); i++){
			bool all_match = true;
			//check if there is enough left in original vector to even match up with repl_this_vector
			if((seq_2_vector.size() - i) < repl_this_vector.size()){
				all_match = false;
			}
			else{ //enough elements to check so check for match
				for(int j = 0; j < repl_this_vector.size(); j++){
					if(seq_2_vector[i + j] != repl_this_vector[j]){
						all_match = false;
						break;
					}
				}
			}

			if(all_match){
				for(int j = 0; j < repl_with_vector.size(); j++){
					changed_vector.push_back(repl_with_vector[j]);
				}
				//need to skip as many spots in original vector as repl_this_vector.size()
				i = i + repl_this_vector.size() - 1; 
			}
			else{
				changed_vector.push_back(seq_2_vector[i]);
			}
		}

		std::string str_to_print = whatev_to_string(changed_vector, true);
		input_box_2->ChangeValue(str_to_print);
		
		evt.Skip();
	}
	catch(...){
		std::cout << "exception, you did something wrong" << std::endl;
	}
}

void cMain::OnMvOutToSeq1ButtonClicked(wxCommandEvent& evt){
	try{
		input_box_1->ChangeValue(output_box_1->GetValue());
		evt.Skip();
	}
	catch(...){
		std::cout << "exception, you did something wrong" << std::endl;
	}
}

void cMain::OnMvOutToSeq2ButtonClicked(wxCommandEvent& evt){
	try{
		input_box_2->ChangeValue(output_box_1->GetValue());
		evt.Skip();
	}
	catch(...){
		std::cout << "exception, you did something wrong" << std::endl;
	}
}

void cMain::OnSeq1ModByAddByButtonClicked(wxCommandEvent& evt){
	try{
		std::string seq_1_txt = std::string(input_box_1->GetValue());
		std::vector <int> seq_1_vector = comma_sep_str_to_int_vector(seq_1_txt);
		int mod_by = std::atoi(seq_1_param_1_box->GetValue());
		//check if mod_by is 0 and return if so, otherwise will crash
		if(mod_by == 0){
			return;
		}
		int add_by = std::atoi(seq_1_param_2_box->GetValue());
		std::vector <int> modified_vector = mod_all_vector_by_certain_amount_and_add_by_certain_amount(seq_1_vector, mod_by, add_by, false);
		std::string string_to_print = whatev_to_string(modified_vector, true);
		input_box_1->ChangeValue(string_to_print);
		evt.Skip();
	}
	catch(...){
		std::cout << "exception, you did something wrong" << std::endl;
	}	
}

void cMain::OnSeq2ModByAddByButtonClicked(wxCommandEvent& evt){
	try{
		std::string seq_2_txt = std::string(input_box_2->GetValue());
		std::vector <int> seq_2_vector = comma_sep_str_to_int_vector(seq_2_txt);
		int mod_by = std::atoi(seq_2_param_1_box->GetValue());
		//check if mod_by is 0 and return if so, otherwise will crash
		if(mod_by == 0){
			return;
		}
		int add_by = std::atoi(seq_2_param_2_box->GetValue());
		std::vector <int> modified_vector = mod_all_vector_by_certain_amount_and_add_by_certain_amount(seq_2_vector, mod_by, add_by, false);
		std::string string_to_print = whatev_to_string(modified_vector, true);
		input_box_2->ChangeValue(string_to_print);
		evt.Skip();
	}
	catch(...){
		std::cout << "exception, you did something wrong" << std::endl;
	}	
}

void cMain::OnSeq1AddByModByButtonClicked(wxCommandEvent& evt){
	try{
		std::string seq_1_txt = std::string(input_box_1->GetValue());
		std::vector <int> seq_1_vector = comma_sep_str_to_int_vector(seq_1_txt);
		int mod_by = std::atoi(seq_1_param_1_box->GetValue());
		int add_by = std::atoi(seq_1_param_2_box->GetValue());
		std::vector <int> modified_vector = mod_all_vector_by_certain_amount_and_add_by_certain_amount(seq_1_vector, mod_by, add_by, true);
		std::string string_to_print = whatev_to_string(modified_vector, true);
		input_box_1->ChangeValue(string_to_print);
		evt.Skip();
	}
	catch(...){
		std::cout << "exception, you did something wrong" << std::endl;
	}	
}

void cMain::OnSeq2AddByModByButtonClicked(wxCommandEvent& evt){
	try{
		std::string seq_2_txt = std::string(input_box_2->GetValue());
		std::vector <int> seq_2_vector = comma_sep_str_to_int_vector(seq_2_txt);
		int mod_by = std::atoi(seq_2_param_1_box->GetValue());
		int add_by = std::atoi(seq_2_param_2_box->GetValue());
		std::vector <int> modified_vector = mod_all_vector_by_certain_amount_and_add_by_certain_amount(seq_2_vector, mod_by, add_by, true);
		std::string string_to_print = whatev_to_string(modified_vector, true);
		input_box_2->ChangeValue(string_to_print);
		evt.Skip();
	}
	catch(...){
		std::cout << "exception, you did something wrong" << std::endl;
	}	
}

void cMain::OnMultSeqsByScalarsAddTogetherModButtonClicked(wxCommandEvent& evt){
	try{
		std::string seq_1_txt = std::string(input_box_1->GetValue());
		std::vector <int> seq_1_vector = comma_sep_str_to_int_vector(seq_1_txt);
		std::string seq_2_txt = std::string(input_box_2->GetValue());
		std::vector <int> seq_2_vector = comma_sep_str_to_int_vector(seq_2_txt);
		int seq_1_scalar = std::atoi(seq_1_scalar_box->GetValue());
		int seq_2_scalar = std::atoi(seq_2_scalar_box->GetValue());
		int mod_by = std::atoi(mod_by_box->GetValue());
		//if vectors are not the same size it will truncate the longer one to the shorter one's size
		std::vector <int> modified_vector = add_two_vectors_ability_to_mult_by_scalars_too(seq_1_vector, seq_1_scalar, seq_2_vector, seq_2_scalar, mod_by);
		std::string string_to_print = whatev_to_string(modified_vector, true);	
		output_box_1->ChangeValue(string_to_print);
		evt.Skip();
	}
		catch(...){
		std::cout << "exception, you did something wrong" << std::endl;
	}
}

void cMain::OnSeq1RotateLeftButtonClicked(wxCommandEvent& evt){
	try{
		std::string seq_1_txt = std::string(input_box_1->GetValue());
		std::vector <int> seq_1_vector = comma_sep_str_to_int_vector(seq_1_txt);
		//copy vector
		std::vector <int> copy;
		for(int i = 0; i < seq_1_vector.size(); i++){
			copy.push_back(seq_1_vector[i]);
		}
		//rotate left
		for(int i = 0; i < seq_1_vector.size(); i++){
			seq_1_vector[i] = copy[(i + 1) % seq_1_vector.size()];
		}
		std::string string_to_print = whatev_to_string(seq_1_vector, true);
		input_box_1->ChangeValue(string_to_print);	
		evt.Skip();
	}
	catch(...){
		std::cout << "exception, you did something wrong" << std::endl;
	}
}

void cMain::OnSeq1RotateRightButtonClicked(wxCommandEvent& evt){
	try{
		std::string seq_1_txt = std::string(input_box_1->GetValue());
		std::vector <int> seq_1_vector = comma_sep_str_to_int_vector(seq_1_txt);
		//copy vector
		std::vector <int> copy;
		for(int i = 0; i < seq_1_vector.size(); i++){
			copy.push_back(seq_1_vector[i]);
		}
		//rotate right
		for(int i = 0; i < seq_1_vector.size(); i++){
			seq_1_vector[(i + 1) % seq_1_vector.size()] = copy[i];
		}
		std::string string_to_print = whatev_to_string(seq_1_vector, true);
		input_box_1->ChangeValue(string_to_print);
		evt.Skip();
	}
	catch(...){
		std::cout << "exception, you did something wrong" << std::endl;
	}
}

void cMain::OnSeq2RotateLeftButtonClicked(wxCommandEvent& evt){
	try{
		std::string seq_2_txt = std::string(input_box_2->GetValue());
		std::vector <int> seq_2_vector = comma_sep_str_to_int_vector(seq_2_txt);
		//copy vector
		std::vector <int> copy;
		for(int i = 0; i < seq_2_vector.size(); i++){
			copy.push_back(seq_2_vector[i]);
		}
		//rotate left
		for(int i = 0; i < seq_2_vector.size(); i++){
			seq_2_vector[i] = copy[(i + 1) % seq_2_vector.size()];
		}
		std::string string_to_print = whatev_to_string(seq_2_vector, true);
		input_box_2->ChangeValue(string_to_print);	
		evt.Skip();
	}
	catch(...){
		std::cout << "exception, you did something wrong" << std::endl;
	}
}

void cMain::OnSeq2RotateRightButtonClicked(wxCommandEvent& evt){
	try{
		std::string seq_2_txt = std::string(input_box_2->GetValue());
		std::vector <int> seq_2_vector = comma_sep_str_to_int_vector(seq_2_txt);
		//copy vector
		std::vector <int> copy;
		for(int i = 0; i < seq_2_vector.size(); i++){
			copy.push_back(seq_2_vector[i]);
		}
		//rotate right
		for(int i = 0; i < seq_2_vector.size(); i++){
			seq_2_vector[(i + 1) % seq_2_vector.size()] = copy[i];
		}
		std::string string_to_print = whatev_to_string(seq_2_vector, true);
		input_box_2->ChangeValue(string_to_print);	
		evt.Skip();
	}
	catch(...){
		std::cout << "exception, you did something wrong" << std::endl;
	}
}

void cMain::OnSeq1ReverseButtonClicked(wxCommandEvent& evt){
	try{
		std::string seq_1_txt = std::string(input_box_1->GetValue());
		std::vector <int> seq_1_vector = comma_sep_str_to_int_vector(seq_1_txt);
		//copy vector
		std::vector <int> copy;
		for(int i = 0; i < seq_1_vector.size(); i++){
			copy.push_back(seq_1_vector[i]);
		}
		//reverse
		for(int i = 0; i < seq_1_vector.size(); i++){
			seq_1_vector[i] = copy[seq_1_vector.size() - 1 - i];
		}
		std::string string_to_print = whatev_to_string(seq_1_vector, true);
		input_box_1->ChangeValue(string_to_print);	
		evt.Skip();
	}
	catch(...){
		std::cout << "exception, you did something wrong" << std::endl;
	}
}

void cMain::OnSeq2ReverseButtonClicked(wxCommandEvent& evt){
	try{
		std::string seq_2_txt = std::string(input_box_2->GetValue());
		std::vector <int> seq_2_vector = comma_sep_str_to_int_vector(seq_2_txt);
		//copy vector
		std::vector <int> copy;
		for(int i = 0; i < seq_2_vector.size(); i++){
			copy.push_back(seq_2_vector[i]);
		}
		//reverse
		for(int i = 0; i < seq_2_vector.size(); i++){
			seq_2_vector[i] = copy[seq_2_vector.size() - 1 - i];
		}
		std::string string_to_print = whatev_to_string(seq_2_vector, true);
		input_box_2->ChangeValue(string_to_print);	
		evt.Skip();
	}
	catch(...){
		std::cout << "exception, you did something wrong" << std::endl;
	}
}

void cMain::OnSeq1ReplaceAnIntWithAStrButtonClicked(wxCommandEvent& evt){
	try{
		//get text from input_box_1 and put in a vector of ints
		std::string seq_1_txt = std::string(input_box_1->GetValue());
		std::string num_to_replace = std::string(replace_this_input_box->GetValue());
		std::string replacement_str = std::string(replace_with_input_box->GetValue());
		std::regex reg(num_to_replace); //convert int num_to_replace to string for regex
		std::string modified_str = std::regex_replace(seq_1_txt, reg, replacement_str);
		output_box_1->ChangeValue(modified_str);
		evt.Skip();
	}
	catch(...){
		std::cout << "exception, you did something wrong" << std::endl;
	}
}

void cMain::OnSeq2ReplaceAnIntWithAStrButtonClicked(wxCommandEvent& evt){
	try{
		//get text from input_box_1 and put in a vector of ints
		std::string seq_2_txt = std::string(input_box_2->GetValue());
		std::string num_to_replace = std::string(replace_this_input_box->GetValue());
		std::string replacement_str = std::string(replace_with_input_box->GetValue());
		std::regex reg(num_to_replace); //convert int num_to_replace to string for regex
		std::string modified_str = std::regex_replace(seq_2_txt, reg, replacement_str);
		output_box_1->ChangeValue(modified_str);
		evt.Skip();
	}
	catch(...){
		std::cout << "exception, you did something wrong" << std::endl;
	}
}

void cMain::OnSeq1SumInversionButtonClicked(wxCommandEvent& evt){
	try{
		std::string seq_1_txt = std::string(input_box_1->GetValue());
		std::vector <int> seq_1_vector = comma_sep_str_to_int_vector(seq_1_txt);
		int sum_param = std::atoi(seq_1_sum_inv_num_box->GetValue());
		std::vector <int> inverted_vector = sum_inversion(seq_1_vector, sum_param);
		std::string string_to_print = whatev_to_string(inverted_vector, true);
		output_box_1->ChangeValue(string_to_print);
		evt.Skip();
	}
	catch(...){
		std::cout << "exception, you did something wrong" << std::endl;
	}
}

void cMain::OnSeq2SumInversionButtonClicked(wxCommandEvent& evt){
	try{
		std::string seq_2_txt = std::string(input_box_2->GetValue());
		std::vector <int> seq_2_vector = comma_sep_str_to_int_vector(seq_2_txt);
		int sum_param = std::atoi(seq_2_sum_inv_num_box->GetValue());
		std::vector <int> inverted_vector = sum_inversion(seq_2_vector, sum_param);
		std::string string_to_print = whatev_to_string(inverted_vector, true);
		output_box_1->ChangeValue(string_to_print);
		evt.Skip();
	}
	catch(...){
		std::cout << "exception, you did something wrong" << std::endl;
	}
}

void cMain::OnSeq1TowerOfHanoiButtonClicked(wxCommandEvent& evt){
	try{
		std::string seq_1_txt = std::string(input_box_1->GetValue());
		std::vector <int> seq_1_vector = comma_sep_str_to_int_vector(seq_1_txt);
		int num_discs = std::atoi(seq_1_tower_of_hanoi_box->GetValue());
		Tower_Of_Hanoi toh;
		toh.num_discs = num_discs;
		//set up original state with all discs in order on the leftest pole
		std::vector <int> start_pole;
		for(int i = 0; i < num_discs; i++){
			start_pole.push_back(i + 1); //i + 1 because numbering the discs 1 through num_discs
		}
		toh.discs_on_poles.push_back(start_pole);
		std::vector <int> empty_vector_1;
		std::vector <int> empty_vector_2;
		toh.discs_on_poles.push_back(empty_vector_1);
		toh.discs_on_poles.push_back(empty_vector_2);
		//just saving all of the states of the discs on poles in giant array to use
		toh.discs_on_poles_in_time.push_back(toh.discs_on_poles);
			
		//hanoi(number of discs, start pole, other pole, goal pole) 
		toh.hanoi(num_discs, 0, 1, 2);

		//interleave shuffle one by one element whatever you want to call it for all of the poles for all of the times
		std::vector <int> all_shuffled_throughout_all_of_time;
		for(int i = 0; i < toh.discs_on_poles_in_time.size(); i++){
			std::vector <int> all_discs_interleaved_one_point_in_time = toh.multiple_vectors_to_one_vector_one_element_by_one_element(toh.discs_on_poles_in_time[i], seq_1_vector); 
			for(int j = 0; j < all_discs_interleaved_one_point_in_time.size(); j++){
				all_shuffled_throughout_all_of_time.push_back(all_discs_interleaved_one_point_in_time[j]);
			}
		}

		std::string string_to_print = whatev_to_string(all_shuffled_throughout_all_of_time, true);
		output_box_1->ChangeValue(string_to_print);

		evt.Skip();
	}
	catch(...){
		std::cout << "exception, you did something wrong" << std::endl;
	}
}

void cMain::OnSeq2TowerOfHanoiButtonClicked(wxCommandEvent& evt){
	try{
		std::string seq_2_txt = std::string(input_box_2->GetValue());
		std::vector <int> seq_2_vector = comma_sep_str_to_int_vector(seq_2_txt);
		int num_discs = std::atoi(seq_2_tower_of_hanoi_box->GetValue());
		Tower_Of_Hanoi toh;
		toh.num_discs = num_discs;
		//set up original state with all discs in order on the leftest pole
		std::vector <int> start_pole;
		for(int i = 0; i < num_discs; i++){
			start_pole.push_back(i + 1); //i + 1 because numbering the discs 1 through num_discs
		}
		toh.discs_on_poles.push_back(start_pole);
		std::vector <int> empty_vector_1;
		std::vector <int> empty_vector_2;
		toh.discs_on_poles.push_back(empty_vector_1);
		toh.discs_on_poles.push_back(empty_vector_2);
		//just saving all of the states of the discs on poles in giant array to use
		toh.discs_on_poles_in_time.push_back(toh.discs_on_poles);
			
		//hanoi(number of discs, start pole, other pole, goal pole) 
		toh.hanoi(num_discs, 0, 1, 2);

		//interleave shuffle one by one element whatever you want to call it for all of the poles for all of the times
		std::vector <int> all_shuffled_throughout_all_of_time;
		for(int i = 0; i < toh.discs_on_poles_in_time.size(); i++){
			std::vector <int> all_discs_interleaved_one_point_in_time = toh.multiple_vectors_to_one_vector_one_element_by_one_element(toh.discs_on_poles_in_time[i], seq_2_vector); 
			for(int j = 0; j < all_discs_interleaved_one_point_in_time.size(); j++){
				all_shuffled_throughout_all_of_time.push_back(all_discs_interleaved_one_point_in_time[j]);
			}
		}

		std::string string_to_print = whatev_to_string(all_shuffled_throughout_all_of_time, true);
		output_box_1->ChangeValue(string_to_print);

		evt.Skip();
	}
	catch(...){
		std::cout << "exception, you did something wrong" << std::endl;
	}
}

void cMain::OnMvOutToHoldThis1ButtonClicked(wxCommandEvent& evt){
	try{
		hold_this_box_1->ChangeValue(output_box_1->GetValue());
		evt.Skip();
	}
	catch(...){
		std::cout << "exception, you did something wrong" << std::endl;
	}
}

void cMain::OnMvOutToHoldThis2ButtonClicked(wxCommandEvent& evt){
	try{
		hold_this_box_2->ChangeValue(output_box_1->GetValue());
		evt.Skip();
	}
	catch(...){
		std::cout << "exception, you did something wrong" << std::endl;
	}
}

void cMain::OnMvSeq1ToHoldThis1ButtonClicked(wxCommandEvent& evt){
	try{
		hold_this_box_1->ChangeValue(input_box_1->GetValue());
		evt.Skip();
	}
	catch(...){
		std::cout << "exception, you did something wrong" << std::endl;
	}
}

void cMain::OnMvSeq1ToHoldThis2ButtonClicked(wxCommandEvent& evt){
	try{
		hold_this_box_2->ChangeValue(input_box_1->GetValue());
		evt.Skip();
	}
	catch(...){
		std::cout << "exception, you did something wrong" << std::endl;
	}
}

void cMain::OnMvSeq2ToHoldThis1ButtonClicked(wxCommandEvent& evt){
	try{
		hold_this_box_1->ChangeValue(input_box_2->GetValue());
		evt.Skip();
	}
	catch(...){
		std::cout << "exception, you did something wrong" << std::endl;
	}
}

void cMain::OnMvSeq2ToHoldThis2ButtonClicked(wxCommandEvent& evt){
	try{
		hold_this_box_2->ChangeValue(input_box_2->GetValue());
		evt.Skip();
	}
	catch(...){
		std::cout << "exception, you did something wrong" << std::endl;
	}
}

//convert whatever vector type to output string keep commas or not
template <class flam>
std::string cMain::whatev_to_string(std::vector <flam> incoming_vect, bool keep_commas) {
	std::ostringstream output_string_holder;
	if (keep_commas) {
		for (int a = 0; a < incoming_vect.size(); a++) {
			if (a == incoming_vect.size() - 1) {
				output_string_holder << incoming_vect[a];
			}
			else {
				output_string_holder << incoming_vect[a] << ", ";
			}
		}
	}
	else {
		for (int a = 0; a < incoming_vect.size(); a++) {
			if (a == incoming_vect.size() - 1) {
				output_string_holder << incoming_vect[a] << "\n";
			}
			else {
				output_string_holder << incoming_vect[a];
			}
		}
	}

	std::string output_string = output_string_holder.str();
	return output_string;
}

std::vector <int> cMain::comma_sep_str_to_int_vector(std::string str) {
	std::stringstream ss(str);
	std::vector <int> int_vect;

	while (ss.good()) {
		std::string substr;
		getline(ss, substr, ',');
		int_vect.push_back(stoi(substr));
	}

	return int_vect;
}

//pass in however many vectors in a 2D vector of all of them
//and returns 1 vector that pulls from the front of each until all have been used
//input vectors can be different sizes
std::vector <int> cMain::multiple_vectors_to_one_vector_one_element_by_one_element(std::vector < std::vector <int> > all_vectors){
    std::vector <int> shuffled_together_vector;
    int num_vectors = all_vectors.size();
    std::vector <int> num_elements_each_vector;
    //get size of each vector
    for(int i = 0; i < num_vectors; i++){
        num_elements_each_vector.push_back(all_vectors[i].size());
    }

    while(true){
        //check if no elements are left in any vector
        bool no_elements = true;
        for(int i = 0; i < num_vectors; i++){
            if(num_elements_each_vector[i] > 0){
                no_elements = false;
            }
        }
        if(no_elements){ //used all of the elements from all of the vectors
            break;
        }
        for(int i = 0; i < num_vectors; i++){
            if(num_elements_each_vector[i] > 0){
                shuffled_together_vector.push_back(all_vectors[i][0]);
                all_vectors[i].erase(all_vectors[i].begin());
                num_elements_each_vector[i]--;
            }
        }
    }

    return shuffled_together_vector;

}

std::vector <int> cMain::mod_all_vector_by_certain_amount_and_add_by_certain_amount(std::vector <int> the_vector, int mod_by, int add_to, bool add_first){
    //try, catch still doesn't prevent program from crashing when the mod by box is empty or contains 0
	//checking if mod_by is 0 in OnSeq1ModByAddByButtonClicked and OnSeq2ModByAddByButtonClicked does the trick
	try{
		std::vector <int> ret_vect;
		if(add_first){
			for(int i = 0; i < the_vector.size(); i++){
				ret_vect.push_back((the_vector[i] + add_to) % mod_by);
			}
		}
		else{
			for(int i = 0; i < the_vector.size(); i++){
				ret_vect.push_back((the_vector[i] % mod_by) + add_to);
			}
		}

		return ret_vect;
	}
	catch(...){
		std::cout << "exception, you did something wrong" << std::endl;
	}

}

std::vector <int> cMain::add_two_vectors_ability_to_mult_by_scalars_too(std::vector <int> vect_a, int scalar_a, std::vector <int> vect_b, int scalar_b, int mod_by){
    std::vector <int> ret_vect;
	//get smallest vector size
    int smallest_vector_size = 0;
	if(vect_a.size() < vect_b.size()){
		smallest_vector_size = vect_a.size();
	}
	else{
		smallest_vector_size = vect_b.size();
	}

	int one_result = 0;
    
    //check to that vectors are the same size just as a warning
	//already truncated larger vector if it was necessary
    if(vect_a.size() != vect_b.size()){
        std::cout << "Warning: vectors are not the same size, larger vector will be truncated to make it work" << std::endl;
	}

    //check if modding the results or not
    if(mod_by){
        for(int i = 0; i < smallest_vector_size; i++){
            one_result = (vect_a[i] * scalar_a) + (vect_b[i] * scalar_b);
            one_result = one_result % mod_by;
            ret_vect.push_back(one_result);        
        }
    }
    else{ //mod_or_not was 0 so don't mod result at all
        
        for(int i = 0; i < smallest_vector_size; i++){
            one_result = (vect_a[i] * scalar_a) + (vect_b[i] * scalar_b);
            ret_vect.push_back(one_result);        
        }

    }
    return ret_vect;
}

std::vector <int> cMain::sum_inversion(std::vector <int> orig_seq, int sum_whatev){
    std::vector <int> changed_vector;
    int octave = 12;
    //so you want to take it down to a # in between 0-11
    //then do the sum inversion thing
    //then add back on the # of octaves that you reduced the original by
    for(int i = 0; i < orig_seq.size(); i++){
        int cur_num = orig_seq[i];
        int num_octaves = 0;
        while(cur_num >= 0){
            cur_num = cur_num - octave;
            num_octaves++;
        }
        //add 12 back and decrease # of octaves once since went one more before the while loop condition was violated
        cur_num = cur_num + octave;        
        num_octaves--;
        int inverted_num = ((sum_whatev + octave) - cur_num) % octave;
        inverted_num = inverted_num + (num_octaves * octave);
        changed_vector.push_back(inverted_num);
    }

    return changed_vector;
}

template <class T>
T cMain::Tower_Of_Hanoi::pop_and_return(std::vector <T> &vect){
    T popped = vect[vect.size() - 1];
    vect.pop_back();
    return popped;
}

template <class T>
T cMain::Tower_Of_Hanoi::pop_front_and_return(std::vector <T> &vect){
    T popped = vect[0];
    vect.erase(vect.begin());
    return popped;
}

void cMain::Tower_Of_Hanoi::move(int f, int t){ //f - from, t - to
    int grabbed_disc = pop_and_return(discs_on_poles[f]);
    discs_on_poles[t].push_back(grabbed_disc);

    //just saving all of the states of the discs on poles in giant vector to use 
    //c++ does copy the vector when you do this, not just point to original vector
    discs_on_poles_in_time.push_back(discs_on_poles);
    //num_moves++;
    //global_num_moves++;
}

//the power is in how it's defined and how you think about that relation in general
//move f - from using h - helper to t - to
void cMain::Tower_Of_Hanoi::hanoi(int n, int f, int h, int t){ //n - # of discs, f - from, h - helper pole (go between), t - to
    //base case
    if(n == 0){
        return;
    }

    //basically just move twice
    //from helper, then helper to the to
    //recursive call with one less
    //you want to solve the order in the h - helper pole spot for n-1 discs
    hanoi(n - 1, f, t, h);

    //then you can move the last disc to the goal target t - to
    //since already solved the order for n-1 discs at the helper position pole spot
    move(f, t); //the first time this returns it's because the subproblem is to just move the 1 disc from the start to the end

    //then move the already solved helper pole to the target t - to using the f - from pole as the helper this time
    hanoi(n - 1, h, f, t); //solving the situation with 1 less disc will need to be solved and arranged in the alternating non goal helper pole
}

std::vector <int> cMain::Tower_Of_Hanoi::multiple_vectors_to_one_vector_one_element_by_one_element(std::vector < std::vector <int> > all_vectors_one_time, std::vector <int> scale_to_translate_to){
	bool translate_to_scale = true; //set to false if you just want the index #s of discs instead, you prob would never want in this application

	std::vector <int> shuffled_together_vector;
    int num_vectors = all_vectors_one_time.size();
    std::vector <int> num_elements_each_vector;
    for(int i = 0; i < num_vectors; i++){
        num_elements_each_vector.push_back(all_vectors_one_time[i].size());
    }

    //sequence is going from pole A to B to C 
    //always picking the disc from the bottom
    //throughout all of time
    while(true){
        bool no_elements = true;
        //check to see if still an element in any vector to add, if not break
        for(int i = 0; i < num_vectors; i++){
            if(num_elements_each_vector[i] > 0){
                no_elements = false;
            }
        }
        if(no_elements){ //used all of the elements from all of the vectors
            break;
        }

        for(int i = 0; i < num_vectors; i++){
            if(num_elements_each_vector[i] > 0){
                //pop 1st element (bottom disc)
                int popped = pop_front_and_return(all_vectors_one_time[i]); //need to pop front
                if(translate_to_scale){
                    shuffled_together_vector.push_back(scale_to_translate_to[(popped - 1) % scale_to_translate_to.size()]);
                }
                else{
                    shuffled_together_vector.push_back(popped);
                }

                num_elements_each_vector[i]--;
            }
        }
    }

    return shuffled_together_vector;

}