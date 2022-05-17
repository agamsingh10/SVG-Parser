// ***********************************Name: Agam Singh Kapoor**************** Student Id: 1121452********A3/

'use strict'


const ffi = require('ffi-napi');

// C library API

// Express App (Routes)
const express = require("express");
const app     = express();
const path    = require("path");
const fileUpload = require('express-fileupload');
const isSvg = require('is-svg');

app.use(fileUpload());
app.use(express.static(path.join(__dirname+'/uploads')));

// Minimization
const fs = require('fs');
const JavaScriptObfuscator = require('javascript-obfuscator');
const cheerio = require('cheerio');

// Important, pass in port as in `npm run dev 1234`, do not change
const portNum = process.argv[2];

// Send HTML at root, do not change
app.get('/',function(req,res){
  res.sendFile(path.join(__dirname+'/public/index.html'));
});

// Send Style, do not change
app.get('/style.css',function(req,res){
  //Feel free to change the contents of style.css to prettify your Web app
  res.sendFile(path.join(__dirname+'/public/style.css'));
});

// Send obfuscated JS, do not change
app.get('/index.js',function(req,res){
  fs.readFile(path.join(__dirname+'/public/index.js'), 'utf8', function(err, contents) {
    const minimizedContents = JavaScriptObfuscator.obfuscate(contents, {compact: true, controlFlowFlattening: true});
    res.contentType('application/javascript');
    res.send(minimizedContents._obfuscatedCode);
  });
});

//Respond to POST requests that upload files to uploads/ directory
app.post('/upload', function(req, res) {
  if(!req.files) {
    return res.status(400).send('No files were uploaded.');
  }
 console.log(req.files, "label222222222222")
  let uploadFile = req.files.file || req.files.fileupload;
  var exists =false
//  console.log(uploadFile.name, "upload file")
 fs.readdir("uploads", function(err,files){
   
   files.map(function(file){
    //  console.log(file, "Filessssssss")
     if(file==uploadFile.name)
     {
        
       exists =true
     }
     else
     exists=false  
    
   }) 
 })
  // Use the mv() method to place the file somewhere on your server
  uploadFile.mv('uploads/' + uploadFile.name, function(err) {
    if(err) {
      return res.status(500).send(err);
    }
    if(exists==true){
    res.redirect('/?exists=1');
    res.send(exists)
    console.log("already exists")

    }
    else{
    res.redirect('/');
    }
  }); 
}); 

//Respond to GET requests for files in the uploads/ directory
app.get('/uploads/:name', function(req , res){
  fs.stat('uploads/' + req.params.name, function(err, stat) {
    if(err == null) {
      res.sendFile(path.join(__dirname+'/uploads/' + req.params.name));
    } else {
      console.log('Error in file downloading route: '+err);
      res.send('');
    }
  });
});

//******* Your code goes here ******* 


var ElementType = {
  SVG_IMAGE : 0,
  CIRC: 1,
  RECT: 2,
  PATH: 3,
  GROUP: 4
};


app.get('/foldercontents',function(req,res){
  let fileInfo = [];
  fs.readdir('uploads',(err,files)=>{
    let sharedLib = ffi.Library('./libsvgparser', {
    
      'helpJSON':['string',['string']],
      'getTitle':['string', ['string']],
      'getDesc':['string', ['string']]
      
  
    });
    files.forEach( (file) => {
      if(path.extname(file)!= '.svg'){
        return;
      }
      let fileArr = {};
      fileArr.name = file;
      fileArr.size = fs.statSync("uploads/" + file).size + "kb";
      // console.log(filePr);
      let agampc = sharedLib.helpJSON("uploads/"+file);
      let title= sharedLib.getTitle("uploads/"+file);
      let desc = sharedLib.getDesc("uploads/"+file);

      let parser = JSON.parse(agampc);
      fileArr.rects = parser.numRect;
      fileArr.circs = parser.numCirc;
      fileArr.paths = parser.numPaths;
      fileArr.grps = parser.numGroups;
      
        
          

      fileArr.rectangle = parser.rects;
      fileArr.circle = parser.circs;
      fileArr.paath = parser.paths;
      fileArr.group = parser.groups

      fileArr.attrrect = parser.attrRect;
      fileArr.attrcirc = parser.attrCirc;
      fileArr.attrpath = parser.attrPath;
      fileArr.attrgrp = parser.attrGrp;

      fileArr.title = title;
      fileArr.desc = desc;
      // filePr.rects = parser.numRect;
      file
      //console.log(agampc); 
       console.log(fileArr.attrrect);
      fileInfo.push(fileArr);
    });  
    res.send(fileInfo); 
  });  
    
})  
    

app.get('/addRectangle', (req, res) => {
  console.log(req.query.svgName, req.query.values)
  fs.readFile(path.join(__dirname + '/uploads/' + req.query.svgName), 'utf8', function (err, contents) {
    if (contents) {
      let $ = cheerio.load(contents)
      $('svg').append('<rect ' + req.query.values + '/>')
      var badXml = $.html()
      var xml = badXml.replace(/<\/body>/, '')
      var xml2 = xml.replace(/<\/html>/, '')
      var xml3 = xml2.replace(/<html>/, '')
      var xml4 = xml3.replace(/<body>/, '')
      var xml5 = xml4.replace(/<\/head>/, '')
      var xml6 = xml5.replace(/<head>/, '')
      console.log(xml2)
      if (isSvg(xml6)&&req.query.values.length>0) {
        res.json('valid')
        fs.writeFile(path.join(__dirname + '/uploads/' + req.query.svgName), xml6, 'utf-8', function (err) {
          console.log('file write error : ', err)
        })
      } else {
        res.json('invalid')
      }
    }
  })

}) 









app.get('/addCircle', (req, res) => {
  console.log(req.query.svgName, req.query.values)
  fs.readFile(path.join(__dirname + '/uploads/' + req.query.svgName), 'utf8', function (err, contents) {
    if (contents) {
      let $ = cheerio.load(contents)
      $('svg').append('<circle ' + req.query.values + '/>')
      var badXml = $.html()
      var xml = badXml.replace(/<\/body>/, '')
      var xml2 = xml.replace(/<\/html>/, '')
      var xml3 = xml2.replace(/<html>/, '')
      var xml4 = xml3.replace(/<body>/, '')
      var xml5 = xml4.replace(/<\/head>/, '')
      var xml6 = xml5.replace(/<head>/, '')
      console.log(xml2)
      if (isSvg(xml6)&&req.query.values.length>0) {
        res.json('valid')
        fs.writeFile(path.join(__dirname + '/uploads/' + req.query.svgName), xml6, 'utf-8', function (err) {
          console.log('file write error : ', err)
        })
      } else {
        res.json('invalid')

      }
      // res.json({ title: title, description: description })
    }
  })

})

//Sample endpoint
app.get('/endpoint1', function(req , res){
  let retStr = req.query.data1 + " " + req.query.data2;
 
  res.send(
    {
      somethingElse: retStr
    }
  );
});

app.listen(portNum);
console.log('Running app at localhost: ' + portNum);