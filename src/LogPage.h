const char LOG_PAGE[] = R"=====(
<!doctype html>
<html>
<head>
  <title>#DEVICE_NAME# - Data Logger</title>
  <meta name="version" content="1.0.0">
  <style>
  canvas{
    -moz-user-select: none;
    -webkit-user-select: none;
    -ms-user-select: none;
  }
  /* Data Table Styling*/ 
  #dataTable {
    font-family: "Trebuchet MS", Arial, Helvetica, sans-serif;
    border-collapse: collapse;
    width: 100%;
    text-align: center;
  }
  #dataTable td, #dataTable th {
    border: 1px solid #ddd;
    padding: 8px;
  }
  #dataTable tr:nth-child(even){background-color: #f2f2f2;}
  #dataTable tr:hover {background-color: #ddd;}
  #dataTable th {
    padding-top: 12px;
    padding-bottom: 12px;
    text-align: center;
    background-color: #050505;
    color: white;
  }
  </style>
</head>
<body>
  <h1 style="text-align:center; color:red;">#DEVICE_NAME#</h1>
  <h3 style="text-align:center;">NodeMCU Data Logger</h3>
<div>
  <table id="dataTable">
    <tr><th style="width:120px">Time</th><th>Log</th></tr>
  </table>
</div>
<br>
<br>  
<script>
var logValues = [];
var timeStamp = [];
setInterval(function() { getData(); }, 5000);
function getData() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
     //Push the data in array
    var time = new Date().toLocaleTimeString();
    var txt = this.responseText;
    var obj = JSON.parse(txt);
    logValues.push(obj.Message);
    timeStamp.push(time);
    
    //Update Data Table
    var table = document.getElementById("dataTable");
    var row = table.insertRow(1); //Add after headings
    var cell1 = row.insertCell(0);
    var cell2 = row.insertCell(1);
    cell1.innerHTML = time;
    cell2.innerHTML = obj.Message;
    }
  };
  xhttp.open("GET", "readLog", true); //Handle readData server on ESP8266
  xhttp.send();
}
</script>
</body>
</html>
)=====";