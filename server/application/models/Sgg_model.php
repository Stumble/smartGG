<?php
class Sgg_model extends CI_Model {

    public function __construct()
    {
        /*         $this->load->database(); */
    }

    public function status()
    {
        $sql = "select * from `sgg_var` where `var_name` = 'status' limit 1";
        $status = $this->db->query($sql)->row()->var_val;
        return unserialize($status);
    }

    public function moisture()
    {
        $sql = "select * from `sgg_var` where `var_name` = 'moisture' limit 1";
        $moi = $this->db->query($sql)->row()->var_val;
        return $moi;
    }
}