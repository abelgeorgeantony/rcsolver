import datainput from "./solve.js";
selectedrow = 0;
selectedcol = 0;
function colorpicker(row,col) {
    if((row === 0) && (col ===0))
    {
        document.getElementById("colorpicker").setAttribute("hidden","hidden");
        selectedrow = 0;
        selectedcol = 0;
        return(0);
    }
    document.getElementById("colorpicker").removeAttribute("hidden");
    selectedrow = row;
    selectedcol = col;
    return(0);
}

/*function setcolor(color) {
    document.getElementById("r"+selectedrow+"c"+selectedcol).style.backgroundColor = color;
    datainput(selectedrow-1,selectedcol-1,color);
    colorpicker(0,0);
}*/