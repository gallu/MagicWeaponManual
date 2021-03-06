<?php

//
ini_set('display_errors', 'on');
error_reporting(E_ALL);
//
//ini_set('display_errors', 'off');

// MWを使えるようにする
$dir = '/opt/www/MW';
set_include_path(get_include_path() . PATH_SEPARATOR . $dir);

// Smartyを使えるようにする
$dir = '/opt/www/Smarty-3.1.8/libs';
set_include_path(get_include_path() . PATH_SEPARATOR . $dir);

// 基本的なphp.iniの設定各種
require_once('mw_set_ini.inc');
// タイムゾーンの設定
date_default_timezone_set('Asia/Tokyo');

// 基準ディレクトリの設定
$bp = '/home/furu/work/MagicWeaponManual/HelloWorldSmarty/';

// configファイル名
$config       = $bp . 'conf/config.conf';

//
require_once('controller.inc');

//
$co = new controller;
$co->set_base_path($bp);

