var http = require('http');
var fs = require('fs');

var data = "";
fs.readFile("./data.json", "utf8", (err, jsonString) => {
  if (err) {
    console.log("Error reading file from disk:", err);
    return;
  }
  try {
    data = JSON.parse(jsonString);
 
  } catch (err) {
    console.log("Error parsing JSON string:", err);
  }
});


exports.GetSubjectiToppers = function(idx)
{
  console.log("index",idx);
  var lst=[];

  sorted = Object.keys(data).sort(function(a,b){return data[a][idx]-data[b][idx]});
  for( var n in sorted )
  {
    var key=sorted[n];
    var val = data[sorted[n]][idx];
    let obj ={
      key,
      val,
    };
    console.log(sorted[n], data[sorted[n]][idx]);
    lst.push(obj);

  }
  console.log(lst);
  return lst;  
}

exports.GetHighestMarks = function()
{
  var lst={};

  for( var key in data)
  {
    var sum=0;
    for( var marks in data[key])
    {
      sum=sum+data[key][marks];
    }
    lst[key]=sum;

    //console.log(key,sum);
  }

  sorted = Object.keys(lst).sort(function(a,b){return lst[a]-lst[b]});
  //for( var n in sorted )
    //console.log(sorted[n], lst[sorted[n]]);
  return sorted[sorted.length-1];  
}
