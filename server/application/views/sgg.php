
<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="utf-8">
        <title>气体卫士</title>
        <meta name="viewport" content="width=device-width, initial-scale=1.0">

        <!-- Loading Bootstrap -->
        <link href="http://perkfile.b0.upaiyun.com/flip/files/bootstrap/css/bootstrap.css" rel="stylesheet">

        <!-- Loading Flat UI -->
        <link href="http://perkfile.b0.upaiyun.com/flip/files/css/flat-ui.css" rel="stylesheet">
        <link rel="shortcut icon" href="http://perkfile.b0.upaiyun.com/flip/files/images/favicon.ico">

        <style type="text/css" media="screen">
         body {
             background-color: #bfc9ca;
             background-image:url(http://perkfile.b0.upaiyun.com/flip/files/images/login_background.png);
         }
         .login-form {
             max-width: 300px;
             margin-top:50px;
             margin-bottom:50px;
             background-color:#34495e;

         }
         .login-form:before {
             border-color:transparent #34495e transparent transparent
         }
         .headimg {
             margin-bottom:30px;
             text-align:center
         }
         .headimg h4{
             color: white
         }
         .errors {
             text-align:center
         }
         .errors strong{
             color:white
         }
         .mid-content{
             width:300px;
             display:table;
             margin-left:auto;
             margin-right:auto;
         }
         .warning {
             background-color: red;
         }
        </style>
        <!-- HTML5 shim, for IE6-8 support of HTML5 elements. All other JS at the end of file. -->
        <!--[if lt IE 9]>
        <script src="http://perkfile.b0.upaiyun.com/flip/js/html5shiv.js"></script>
        <script src="http://perkfile.b0.upaiyun.com/flip/js/respond.min.js"></script>
        <![endif]-->
    </head>
    <body>
        <div class="container">
            <div class="mid-content">
                <div class="login-form">
                    <div>
                        <div class="headimg">
                            <h4>气体小卫士</h4>
                        </div>
                        <div class="form-group">
                            <div class="input-group">
                                <span class="input-group-addon">家庭综合状态</span>
                                <input style="text-align:center;" type="text" class="form-control" id="status" value="安全"/>
                            </div>
                            <p></p>
                            <?php
                            $namings = array('MQ2', 'MQ7', 'MQ4', 'MQ135', 'TEMPERATURE', 'MOISTURE');

                            foreach ($namings as $name) {
                            ?>
                            <div class="input-group">
                                <span class="input-group-addon"><?php echo $name ?></span>
                                <input type="text" class="form-control" id="<?php
                                                                            if (substr($name, 0, 2) == 'MQ')
                                                                                echo $name . 'A';
                                                                            else
                                                                                echo $name;
                                                                            ?>"/>
                            </div>
                            <p></p>
                            <?php } ?>
                        </div>
                        <button onclick="setMoisture(1)" class="btn btn-large btn-block btn-primary" id="open-moi">
                                    开启加湿器
                        </button>
                        <button onclick="setMoisture(0)" class="btn btn-large btn-block btn-danger" id="close-moi">
                                    关闭加湿器
                        </button>
                    </div>
                </div>
            </div>
        </div>
        <!-- /.container -->


        <!-- Load JS here for greater good =============================-->
        <script src="http://perkfile.b0.upaiyun.com/flip/files/js/jquery-1.8.3.min.js"></script>
        <script src="http://perkfile.b0.upaiyun.com/flip/files/js/jquery-ui-1.10.3.custom.min.js"></script>
        <script src="http://perkfile.b0.upaiyun.com/flip/files/js/jquery.ui.touch-punch.min.js"></script>
        <script src="http://perkfile.b0.upaiyun.com/flip/files/js/bootstrap.min.js"></script>
        <script src="http://perkfile.b0.upaiyun.com/flip/files/js/bootstrap-switch.js"></script>
        <script src="http://perkfile.b0.upaiyun.com/flip/files/js/flatui-checkbox.js"></script>
        <script src="http://perkfile.b0.upaiyun.com/flip/files/js/flatui-radio.js"></script>
        <script src="http://perkfile.b0.upaiyun.com/flip/files/js/jquery.tagsinput.js"></script>
        <script src="http://perkfile.b0.upaiyun.com/flip/files/js/jquery.placeholder.js"></script>
        <script>
         var interval = self.setInterval("clock()",500)
         var alarm_interval = -1;
         var isWarning = false;
         function setInputVal(id, val) {
             $('#' + id).val(val);
         }

         $('<audio id="alarmAudio"><source src="../../files/notify.ogg" type="audio/ogg"></audio>').appendTo('body');//载入声音文件

         function playAlarm() {
             $('#alarmAudio')[0].play(); //播放声音
         }

         function startAlarm() {
             if (isWarning) {
                 return 0;
             }
             isWarning = true;
             alarm_interval = self.setInterval("playAlarm()", 1000);
             setInputVal("status", "检测到可疑气体！");
             $('#status').addClass("warning");
         }

         function stopAlarm() {
             if (!isWarning) {
                 return 0;
             }
             isWarning = false;
             window.clearInterval(alarm_interval);
             setInputVal("status", "安全");
             $('#status').removeClass("warning");
         }

         function clock() {
             $.getJSON("status",function(rst) {
                 isSafe = true;
                 for( key in rst ) {
                     if (key.substr(-1) == "D") {
                         if (rst[key] != 0) {
                             isSafe = false;
                         }
                     } else {
                         setInputVal(key, rst[key]);
                     }
                 }
                 if (isSafe) {
                     if (isWarning) {
                         /* close alarm */
                         stopAlarm();
                     }
                 } else {
                     if (!isWarning) {
                         /* open alarm */
                         startAlarm();
                     }
                 }
             });
         }

         function setMoisture(moiStatus) {
             $.post("setmoisture",{'moisture' : moiStatus},function(json){
                 alert("已操作");
             },"json");
         }
        </script>
    </body>
</html>

