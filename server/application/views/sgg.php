
<script type="text/javascript" src="http://perkfile.b0.upaiyun.com/flip/files/js/jquery-1.8.3.min.js"></script>
<script>
var int = self.setInterval("clock()",50)
function clock() {
     $.getJSON("status",function(rst) {
         if (rst.status == 1) {
             $('body').css("background-color","red");
         } else {
             $('body').css("background-color","green");
         }
     });
 }
</script>