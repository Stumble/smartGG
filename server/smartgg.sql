-- phpMyAdmin SQL Dump
-- version 4.1.12
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: 2016-08-27 14:13:37
-- 服务器版本： 5.6.16
-- PHP Version: 5.5.11

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `smartgg`
--

-- --------------------------------------------------------

--
-- 表的结构 `sgg_var`
--

CREATE TABLE IF NOT EXISTS `sgg_var` (
  `var_name` varchar(15) NOT NULL,
  `var_val` varchar(2000) NOT NULL,
  `var_date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`var_name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- 转存表中的数据 `sgg_var`
--

INSERT INTO `sgg_var` (`var_name`, `var_val`, `var_date`) VALUES
('moisture', '0', '2016-08-27 12:07:43'),
('status', 'a:10:{s:4:"MQ7D";s:1:"4";s:6:"MQ135A";s:1:"7";s:6:"MQ135D";s:1:"8";s:11:"TEMPERATURE";s:1:"9";s:4:"MQ7A";s:1:"3";s:4:"MQ4A";s:1:"5";s:4:"MQ2D";s:1:"2";s:8:"MOISTURE";s:2:"11";s:4:"MQ2A";s:1:"1";s:4:"MQ4D";s:1:"6";}', '2016-08-26 13:32:19');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
