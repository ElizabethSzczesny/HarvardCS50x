const drag = document.getElementById("dragtarget");
const drop = document.getElementById("droptarget");

var append = document.querySelectorAll('.append');

console.log("Hello World");

var counter = 0;

//put all your id's into their own array manually and then looped through that

/*drag.addEventListener("mouseover", function(){
    if(counter == 0){
        var clone = drag.cloneNode(true);
        append[0].appendChild(clone);
        counter += 1
    }
    var node = document.createTextNode('move to match the word pine cone with the image of a pine cone');
    append[0].appendChild(node);
    }
)*/

//Make the DIV element draggagle:


/* Events fired on the drag target */

drag.addEventListener("dragstart", function(event) {
  event.dataTransfer.setData("Text", event.target.id);
});

drag.addEventListener("drag", function(event) {
  //document.getElementById("demo").innerHTML = "The text is being dragged.";
  drop.style.visibility = "visible";
});


/* Events fired on the drop target */
drop.addEventListener("dragover", function(event) {
  event.preventDefault();
  //document.getElementById("demo").innerHTML = "The text is OVER the droptarget.";
  drop.style.visibility = "visible";
  //event.target.style.border = "4px dotted brown";
});

var pagenumber = 1;

drop.addEventListener("drop", function(event) {
  event.preventDefault();
  const data = event.dataTransfer.getData("Text");
  drop.appendChild(document.getElementById(data));
  //document.getElementById("demo").innerHTML = "The text was dropped.";
  drop.style.visibility = "visible";

  if(counter == 0){
    var clone = drag.cloneNode(true);
    append[0].appendChild(clone);
    console.log(clone);
    counter += 1
  } 

  /*setTimeout(turnPage, 5000);
  pagenumber +=1
  if (pagenumber == 5){
    pagenumber = null;
  }*/
});

function turnPage(){
  window.location = "index" + pagenumber + ".html";
}









