var http = require('http');
var fs = require('fs');
var querystring = require('querystring');
const url = require('url');

var service = require('./service.js');
 
let port = 8080

http.createServer(function (req, res) {

var parsed = url.parse(req.url,true).query;
//console.log(parsed.query);


if(parsed.query=='1')
{
  //console.log("topper : ",service.GetHighestMarks());
  res.writeHead(200, {'Content-Type': 'text/html'});
  res.write(" <h3>Student with Highest Total : " + service.GetHighestMarks() + " </h3>"); 
  res.end('');
}
else if(parsed.query=='2' && typeof(parsed.index) == "undefined")
{

 const ht=` 
    <HTML>
    <head>
      <title> SSD Activity 8</title>
    </head>
    <body>

    <form action="http://localhost:8080/" method="GET">
    <input type="text" name="query" value="2" hidden>
    <h3>Enter Index Number (0-4) only: </h3> <input type="text" name="index">
    <button type="submit">enter</button>
    </form>



    </body>
    </HTML>
 `
 
 res.writeHead(200, {'Content-Type': 'text/html'});
 res.write(ht);
 res.end('');

}
else if(parsed.query=='2' && typeof(parsed.index ) != "undefined")
{
  res.writeHead(200, {'Content-Type': 'text/html'});

  if(parsed.index > 4 || parsed.index < 0)
  {
  res.write("<h2>Invalid Index:</h2> <br>" + parsed.index);
  res.end('');

  }
  else
  {
    var lst = service.GetSubjectiToppers(parsed.index);
    //console.log(lst);
    result="";
    for(var s in lst)
    {
      //result=result + lst[s][0] +lst[s][1]+ "<br>";
      //console.log(lst[lst[s]],lst[s]);
    }

    res.write("<h2>List of students in non-decreasing order (Arranged by Index Parameter) :</h2> <br>");
    res.end('');
  }
}
else
{
  res.writeHead(200, {'Content-Type': 'text/html'});
  res.end('Invalid Query');
}


}).listen(port, () => {
  console.log(`Server is now lisning on port ${port}`)
});
