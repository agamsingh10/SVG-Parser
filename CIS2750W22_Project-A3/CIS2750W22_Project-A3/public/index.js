

// Put all onload AJAX calls here, and event listeners


    // let files= [];
    // $.ajax({
    
    //     type: 'get',            //Request type
    //         dataType: 'file',       //Data type - we will use JSON for almost everything 
    //         url: '/upload/:name',   //The server endpoint we are connecting to
    //         data: {
    //             "name": "quad01.svg"
    //         },
    
    //         success: function(data){
    //             console.log(data);
    //         },
    //         fail: function(error){ 
    //             console.log(error);
    //             alert("Failed to fetch server");
    //         }
    // });
    
    
    
    
    
    
    // names=['quad01. svg'];
    var rectarr =[];
    var circarr = [];
    var patharr = [];
    var grparr=[];
    var names=[];
    var attributes = [];
    
    jQuery(document).ready(function() {
        // On page-load AJAX Example
        jQuery.ajax({
            type: 'get',            //Request type
            dataType: 'json',       //Data type - we will use JSON for almost everything 
            url: '/foldercontents',   //The server endpoint we are connecting to
            data: {
                
            },
            success: function (data) {
                /*  Do something with returned object
                    Note that what we get is an object, not a string, 
                    so we do not need to parse it on the server.
                    JavaScript really does handle JSONs seamlessly
                */
               // jQuery('#blah').html("On page load, received string '"+data.somethingElse+"' from server");
                //We write the object to the console to show that the request was successful
                // console.log(data); 
                // names=data;
                // console.log(names);
                data.forEach((element) => {
                    
                    if(element.name.includes('.svg')){
                    
                        names.push(element);
                       
                    }
                    
                });
                if(names.length==0){
                    $(".empty").text();
                }
                else{
                    $(".empty").empty();
                }
// console.log(names);
names.map(function(item, index){
    item.attrrect.map(function(item2,index2){
        attributes.push(item2);
    
    item2.map(function(item3, index3){
        // console.log(item3.name,"name"+index3);
        // console.log(item3.value,"value"+index3);

    })
    })
});
                $('#panel').append("<tr><th>Image</br>(click to download)</th><th>File name</br>(click to</br>download)</th><th>File size</th><th>Number of</br>rectangles</th><th>Number</br>of circles</th><th>Number</br>of Paths</th> <th >Number</br>of group</th></tr>");   
    
    for(let file of names){
        $('#panel').append("<tr><td> <a href=\"uploads/"+file.name+`\" download >      <img  class="imgS" src=\"uploads/` + file.name + "\" download >     </a>" +  "<td> <a href=\"uploads/"+file.name+" \" download >  " + file.name +   "   </a>"  +     "</td><td>" + file.size + 
                    "</td><td>"+ file.rects + 
                    "</td><td>"+ file.circs +
                    "</td><td>"+ file.paths + 
                    "</td><td>" + file.grps + 
                    "</td></tr>");
        
    }

    
    for(let file of names){
         
        $('#dropdown1').append(
            $('<option/>')
            // .addClass("option")
            .text(file.name)
        );
    }
    for(let file of names){
         
        $('#dropdown2').append(
            $('<option/>')
            // .addClass("option")
            .text(file.name)
        );
    }
    for(let file of names){
         
        $('#dropdown3').append(
            $('<option/>')
            // .addClass("option")
            .text(file.name)
        );
    }

    

    

    $('#temp').append("<tr><th>Title</th><th>Description</th></tr>");
    $('#remp2').append("<tr><th>Component</th><th>Summary</th>"+`<th>Other Attributes</th></tr>`);
   
   
    

        
    // })
    

                // console.log(names);
            },
            fail: function(error) {
                // Non-200 return, do something with error
                $('#blah').html("On page load, received error from server");
                console.log(error); 
            }


        });


        

        

        
    
    
    
    
    
    
    
        // Event listener form example , we can use this instead explicitly listening for events
        // No redirects if possible
        $('#someform').submit(function(e){
            $('#blah').html("Form has data: "+$('#entryBox').val());
            e.preventDefault();
            //Pass data to the Ajax call, so it gets passed to the server
            $.ajax({
                //Create an object for connecting to another waypoint
            });
        });
    
    //   function ad dListeners(button, ListenTo){
    
    //   } 
    
    
     


$("#uploadbtn").on('click', async ()=>{
    
    let formData = new FormData();           
    formData.append("file", fileupload.files[0]);
    console.log(fileupload.files[0])
    var exists=false
    names.map(async function(file){
        //  console.log(fileupload.files[0].name, "Files namesssssss")
        
         if(file.name==fileupload.files[0].name)
         {
            window.alert("This file already exists, Try with another file")
            exists=true
         }
         else{ 
             exists=false
            
          }
        
       }) 

       if(exists==false){
       await fetch('/upload', {
        method: "POST", 
        body: formData
      }).then((res)=>{
          console.log(res,"Upload Response");
      
      }).catch((err)=>{
          // alert('The file already exists. Try another file');
          console.log(err,"Upload Error")
      })
    }
   
})
    
        
    }); 
 
    function DeleteRows() {
        var rowCount = remp2.rows.length;
        for (var i = rowCount - 1; i > 0; i--) {
             remp2.deleteRow(i);
        }
       
    }
 
    function DeleteRows2() {
        
        var rowCount2 = temp.rows.length;
        
        for (var i = rowCount2 - 1; i > 1; i--) {
            temp.deleteRow(i);
       }
    }
    
    

    let count=0; 
    let count1=0
    function getval(){

       // $('#temp3').empty(); 
        
        if(count!=0){    
            DeleteRows();  
        } 
        
        $('#imgSi')   
        .attr("src", $("#dropdown1 option:selected").text());
        let lul=$("#dropdown1 option:selected").text();
        //console.log(lul);
        

        for(let file of names){
             

            // $("#remp2").remove();
             
            if(file.name==lul){
                
                rectarr=[];
                circarr=[];
                patharr=[];
                grparr=[];

                rectarr.push(file.attrrect);
                circarr.push(file.attrcirc);
                patharr.push(file.attrpath);
                grparr.push(file.attrgrp);
                // DeleteRows2();
                if(count1!=0){
                $("#temp").empty();
    $('#temp').append("<tr><th>Title</th><th>Description</th></tr>");
                
            }
                let $titdesc = $(
                    `
                    <tr class='clear width'>
                    <td><label>Title  :</label>
                    
                    <input type="text" name="title" value="${file.title}" placeholder="Enter Title"></td>
                    
                    
                    <td ><label>Description  :</label>
                    
                    <input type="text" name="desc" value="${file.desc}" placeholder="Enter Title"></td>
                    </tr>
                    <tr>
                    <td colspan = "2"><input type="submit" name="tDbtn" value="Save changes" id="special"></td>    
                    </tr>
                    `
                )
                count1++
                $titdesc.appendTo($('#temp'))
                
                // console.log(rectarr, "rect arr"); 
            
            if (file.rectangle.length > 0)
            {   
                for (var i = 0 ; i < file.rectangle.length ; i ++) {
                   
                    $("#remp2").append("<tr><td>Rectangle "+ (i + 1) +`</td><td> Upper left corner: x = <p contenteditable="true">` + file.rectangle[i].x + `cm</p> y = <p contenteditable="true">` + file.rectangle[i].y + `cm </p>Width = <p contenteditable="true">` +file.rectangle[i].w + `cm</p> Height= <p contenteditable="true">` +file.rectangle[i].h + `cm</p><button class="changes">Submit changes</button</td><td>` + file.rectangle[i].numAttr + "</td></tr>");
                } 
            } 
            if (file.circle.length > 0)
            {
                for (var i = 0 ; i < file.circle.length ; i ++) {
                   
                    $("#remp2").append("<tr><td>Circle "+ (i + 1) +`</td><td> Center: x =<p contenteditable="true"> ` + file.circle[i].cx + `cm</p> y = <p contenteditable="true">` +file.circle[i].cy + `cm</p> Radius = <p contenteditable="true">` +file.circle[i].r + `cm</p><button class="changes">Submit changes</button</td><td>` +file.circle[i].numAttr + "</td></tr>");
                }
            }
            if (file.paath.length > 0)
            {
                for (var i = 0 ; i < file.paath.length ; i ++) {
                    
                    $("#remp2").append("<tr><td>Path "+ (i + 1) +`</td><td> Path data = <p contenteditable="true">` + file.paath[i].d + `cm</p><button class="changes">Submit changes</button</td><td>` + file.paath[i].numAttr + "</td></tr>");
                }
            }
            if (file.group.length > 0)
            {
                for (var i = 0 ; i < file.group.length ; i ++) {

                    $("#remp2").append("<tr><td>Group "+ (i + 1) +"</td><td >" + file.group[i].children + " child elements</td><td>" + file.group[i].numAttr + "</td></tr>");
                   
                }
            } 
            count=count +1;       
            break;
        }
       

    }
  

    }  
    
    $("#dropdown1").on("change",function(e){
        $("#temp3div").html("");
        getval(e);
    });

    $(document).on("click",".changes",function(){
        alert("This is only used for frontend part, Does not change attributes in backend");
        window.location.reload();
    });

let cnt=0 , countt=0
$("#btn").click(function(){
    $("#temp3div").html("");
    let isclick=0, isS=0;
    // $("#temp3div").append("<div/>")
    // .addClass("temp3item")
    if(rectarr.length>0){
    rectarr.map(function(item,index){
        
        
        item.map(function(item2,index2){

   $("#shapeRect"+index2).html("")

    $('#temp3div').append(`<div class="temp3item"` + `id=shapeRect`+ index2 + `> ` +`</div>`
        )

        $("#shapeRect"+index2).append("<h1>Rectangle"+parseInt(index2+1)+"</h1>")
        cnt=0
            item2.map(function(item3, index3){
                $(`#shapeRect`+ index2).append(`<p contenteditable="true">` + item3.name+` </p>: <p contenteditable="true">`+ item3.value+ ` `+ `</p>`)
             cnt++;  

                
            })
            
            $(`#shapeRect`+ index2).append(`<button id='button`+ index2+`'>Add Attribute</button> `).on("click", function(){
                countt++;

                if(isclick==0 ){
                $(`#shapeRect`+ index2).append(`<div class="shapeDiv"><p> Attribute Name: </p><input/></div>`)
                $(`#shapeRect`+ index2).append(`<div class="shapeDiv"><p> Attribute Value: </p><input/></div>`)

                $(`#shapeRect`+ index2).append("<button>SUBMIT</button>").on("click",function(){
                    if(isS==cnt+3){
                        alert("This does not work in back end, only for front end")
                    window.location.reload()
                    
                    }
                    isS++
                })
                isclick=1
                }
                            })

            
            
            // console.log(item2, "attr item");
        })
       
    })
    
    }if(circarr.length>0){
        circarr.map(function(item,index){
            
            
            item.map(function(item2,index2){
    
       $("#shapeCirc"+index2).html("")
    
        $('#temp3div').append(`<div class="temp3item"` + `id=shapeCirc`+ index2 + `> ` +`</div>`
            )
    
            $("#shapeCirc"+index2).append("<h1>Circle"+parseInt(index2+1)+"</h1>")
            cnt=0
                item2.map(function(item3, index3){
                    $(`#shapeCirc`+ index2).append(`<p contenteditable="true">` + item3.name+`</p> : <p contenteditable="true"> `+ item3.value+ ` `+ `</p>`)
    
                    cnt++
                })
                
                $(`#shapeCirc`+ index2).append(`<button id='button`+ index2+`'>Add Attribute</button> `).on("click", function(){
                    
    
                    if(isclick==0){
                    $(`#shapeCirc`+ index2).append(`<div class="shapeDiv"><p> Attribute Name: </p><input/></div>`)
                    $(`#shapeCirc`+ index2).append(`<div class="shapeDiv"><p> Attribute Value: </p><input/></div>`)
    
                    $(`#shapeCirc`+ index2).append("<button>SUBMIT</button>").on("click",function(){
                        if(isS==cnt+5){
                        window.location.reload()
                        
                        }
                        isS++
                    })
                    isclick=1
                    }
                                })
    
                
                
                // console.log(item2, "attr item");
            })
           
        })
        
        }

        if(patharr.length>0){
            patharr.map(function(item,index){
                
                
                item.map(function(item2,index2){
        
           $("#shapePath"+index2).html("")
        
            $('#temp3div').append(`<div class="temp3item"` + `id=shapePath`+ index2 + `> ` +`</div>`
                )
        
                $("#shapePath"+index2).append("<h1>Path"+parseInt(index2+1)+"</h1>")
                cnt=0
                    item2.map(function(item3, index3){
                        $(`#shapePath`+ index2).append(`<p contenteditable="true">` + item3.name+` </p> :<p contenteditable="true"> `+ item3.value+ ` `+ `</p>`)
        cnt++
                        
                    })
                    
                    $(`#shapePath`+ index2).append(`<button id='button`+ index2+`'>Add Attribute</button> `).on("click", function(){
                        
        
                        if(isclick==0){
                        $(`#shapePath`+ index2).append(`<div class="shapeDiv"><p> Attribute Name: </p><input/></div>`)
                        $(`#shapePath`+ index2).append(`<div class="shapeDiv"><p> Attribute Value: </p><input/></div>`)
        
                        $(`#shapePath`+ index2).append("<button>SUBMIT</button>").on("click",function(){
                            if(isS==cnt+5){
                            window.location.reload()
                            
                            }
                            isS++
                        })
                        isclick=1
                        }
                                    })
        
                    
                    
                    // console.log(item2, "attr item");
                })
               
            })
            
            }

            if(grparr.length>0){
                grparr.map(function(item,index){
                    
                    
                    item.map(function(item2,index2){
            
               $("#shapeGrp"+index2).html("")
            
                $('#temp3div').append(`<div class="temp3item"` + `id=shapeGrp`+ index2 + `> ` +`</div>`
                    )
            
                    $("#shapeGrp"+index2).append("<h1>Group"+parseInt(index2+1)+"</h1>")
                    cnt=0
                        item2.map(function(item3, index3){
                            $(`#shapeGrp`+ index2).append(`<p contenteditable="true">` + item3.name+`</p> : <pcontenteditable="true">`+ item3.value+ ` `+ `</p>`)
            
                            cnt++
                        })
                        
                        $(`#shapeGrp`+ index2).append(`<button id='button`+ index2+`'>Add Attribute</button> `).on("click", function(){
                            
            
                            if(isclick==0){
                            $(`#shapeGrp`+ index2).append(`<div class="shapeDiv"><p> Attribute Name: </p><input/></div>`)
                            $(`#shapeGrp`+ index2).append(`<div class="shapeDiv"><p> Attribute Value: </p><input/></div>`)
            
                            $(`#shapeGrp`+ index2).append("<button>SUBMIT</button>").on("click",function(){
                                if(isS==cnt+5){
                                window.location.reload()
                                
                                }
                                isS++
                            })
                            isclick=1
                            }
                                        })
            
                        
                        
                        // console.log(item2, "attr item");
                    })
                   
                })
                
                }
                // $('html,body').animate({ scrollTop: 99999999 }, 'slow');
    
//     


$("#temp3div").slideToggle(800);

});



$('#shapeRect').on('click', () => {
    jQuery.ajax({
        type: 'get',            //Request type
        dataType: 'json',       //Data type - we will use JSON for almost everything 
        url: '/addRectangle',   //The server endpoint we are connecting to
        dataType: "json",
        contentType: "application/json",
        data: {
            values: document.getElementById("rectvalue").value,
            svgName: $('#dropdown2').val(),
        },
        success: function (data) {
            if (data == 'valid') {
                alert("Rectangle added successfully")
                location.reload()
            } else {
                alert("Please enter in proper format,try again.")
            }
        },
        fail: function (error) {
            // Non-200 return, do something with error
            console.log(error);
        }
    });
})
 
$('#shapeCirc').on('click', () => {
    jQuery.ajax({
        type: 'get',            //Request type
        dataType: 'json',       //Data type - we will use JSON for almost everything 
        url: '/addCircle',   //The server endpoint we are connecting to
        dataType: "json",
        contentType: "application/json",
        data: {
            values: document.getElementById("circvalue").value,
            svgName: $('#dropdown2').val(),
        },
        success: function (data) {
            if (data == 'valid') {
                alert("Circle added successfully")
                location.reload()
            } else {
                alert("Please enter in proper format,try again.")
            }
        },
        fail: function (error) {
            // Non-200 return, do something with error
            console.log(error);
        }
    });
})



$(document).on("click","#scaleSubrect",function(){
    alert("This is only used for frontend part, Does not scale image in backend");
    window.location.reload();
});

$(document).on("click","#scaleSubcirc",function(){
    alert("This is only used for frontend part, Does not scale image in backend");
    window.location.reload();
});

$(document).on("click","#special",function(){
    alert("This is only used for frontend part, Does not save content in backend");
    window.location.reload();
});

$("#add").on("click",function(){
    $("#new").append("<tr><th>Image</br>(click to download)</th><th>File name</br>(click to</br>download)</th><th>File size</th></tr>")
})
    
$(document).on("click","#submit",function(){
    alert("This is only used for frontend part, Does not scale in backend");
    window.location.reload();
});


// $(".haha").click(function(){
//     window.location.reload();
// })
             
// $("#shapeSub").click(function(){
//     window.location.reload();
// })

$("#create").click(function(){
    alert("This is only used for frontend part, Does not create svg in backend");
    window.location.reload();
})

$("#add").click(function(){
    alert("create svg not working in backend so no add shape for it.");
    window.location.reload();
})
// $(document).on("change","shappes",function(){
//         $('#imgSi')
//         .attr("src", $("#file-options option:selected").text());
// })


