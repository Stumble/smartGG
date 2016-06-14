<?php
defined('BASEPATH') OR exit('No direct script access allowed');

$key = "srtp";

class Sgg extends CI_Controller {

    public function __construct()
    {
        parent::__construct();
        $this->load->model('Sgg_model');
    }

    public function index()
	{
        $status = $this->Sgg_model->status();
        $this->load->view("sgg", array('status' => $status));
	}

    public function status()
    {
        $status = $this->Sgg_model->status();
        echo json_encode(
            array(
                "status" => $status,
            )
        );
    }

    public function update()
    {
        $data = $this->input->post();
        $this->db->where('var_name', 'status');
        $this->db->update('sgg_var', array('var_val' => $data['status']));
        /* todo: signature check */
    }
}
