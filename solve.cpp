#include<iostream>
#include<stdlib.h>
using namespace std;

struct edge
{
    const string color1;
    const string color2;
};

struct corner
{
    const string color1;
    const string color2;
    const string color3;
};

struct centre
{
    const string color;
    edge* edge1;
    edge* edge2;
    edge* edge3;
    edge* edge4;
    corner* corner1;
    corner* corner2;
    corner* corner3;
    corner* corner4;
};

edge arr_edges[12] = {
    {"white","red"},
    {"white","green"},
    {"white","orange"},
    {"white","blue"},
    {"yellow","red"},
    {"yellow","blue"},
    {"yellow","orange"},
    {"yellow","green"},
    {"red","green"},
    {"red","blue"},
    {"orange","green"},
    {"orange","blue"}
};
/////////////////////////////////////////////////
corner arr_corners[8] = {
    {"white","red","blue"},
    {"white","red","green"},
    {"white","orange","green"},
    {"white","orange","blue"},
    {"yellow","red","green"},
    {"yellow","red","blue"},
    {"yellow","orange","blue"},
    {"yellow","orange","green"}
};

/////////////////////////////////////////////////
centre white = {"white"};
centre red = {"red"};
centre yellow = {"yellow"};
centre orange = {"orange"};
centre blue = {"blue"};
centre green = {"green"};

enum pieces {CORNER,EDGE,CENTRE};
typedef struct
{
    int piecetag;
    corner *corner_;
    edge *edge_;
    centre *centre_;
} cube;

cube new_corner(corner *piecetoadd)
{
    cube arr_element;
    arr_element.piecetag = CORNER;
    arr_element.corner_ = piecetoadd;
    return arr_element;
}
cube new_edge(edge *piecetoadd)
{
    cube arr_element;
    arr_element.piecetag = EDGE;
    arr_element.edge_ = piecetoadd;
    return arr_element;
}
cube new_centre(centre *piecetoadd)
{
    cube arr_element;
    arr_element.piecetag = CENTRE;
    arr_element.centre_ = piecetoadd;
    return arr_element;
}

cube cubearr[3][3][3];



/*
void solvedcube()
{
    white.edge1 = &e1;
    red.edge1 = &e1;

    white.edge2 = &e2;
    green.edge1 = &e2;

    white.edge3 = &e3;
    orange.edge1 = &e3;

    white.edge4 = &e4;
    blue.edge1 = &e4;

    yellow.edge1 = &e5;
    red.edge2 = &e5;

    yellow.edge2 = &e6;
    blue.edge2 = &e6;

    yellow.edge3 = &e7;
    orange.edge2 = &e7;

    yellow.edge4 = &e8;
    green.edge2 = &e8;

    red.edge3 = &e9;
    green.edge3 = &e9;

    red.edge4 = &e10;
    blue.edge3 = &e10;
    
    orange.edge3 = &e11;
    green.edge4 = &e11;

    orange.edge4 = &e12;
    blue.edge4 = &e12;
    ////////////////////
    white.corner1 = &c1;
    red.corner1 = &c1;
    blue.corner1 = &c1;

    white.corner2 = &c2;
    red.corner2 = &c2;
    green.corner1 = &c2;

    white.corner3 = &c3;
    orange.corner1 = &c3;
    green.corner2 = &c3;

    white.corner4 = &c4;
    orange.corner2 = &c4;
    blue.corner2 = &c4;

    yellow.corner1 = &c5;
    red.corner3 = &c5;
    green.corner3 = &c5;

    yellow.corner2 = &c6;
    red.corner4 = &c6;
    blue.corner3 = &c6;

    yellow.corner3 = &c7;
    orange.corner3 = &c7;
    blue.corner4 = &c7;

    yellow.corner4 = &c8;
    orange.corner4 = &c8;
    green.corner4 = &c8;
}
*/

void doinput();
void inputside(string [3][3]);
void displayside(string [3][3]);
void horizontal();
void spacer();
void spacerundscr();
void longspacer();
void spacer(string);
bool vaildcolor(string);
void connectpieces();
corner& findcorner(int,int,int);

string whiteside[3][3] = {"","","","","white","","","",""};
string redside[3][3] = {"","","","","red","","","",""};
string greenside[3][3] = {"","","","","green","","","",""};
string orangeside[3][3] = {"","","","","orange","","","",""};
string blueside[3][3] = {"","","","","blue","","","",""};
string yellowside[3][3] = {"","","","","yellow","","","",""};




int main()
{
    doinput();
    cout<<&findcorner(0,0,0);
    //connectpieces();
    return(0);
}


void connectpieces()
{
    //cubearr[1][1][1] = NULL; // core of the cube!

    cubearr[1][1][0] = new_centre(&white);
    cubearr[1][0][1] = new_centre(&red);
    cubearr[2][1][1] = new_centre(&green);
    cubearr[1][2][1] = new_centre(&orange);
    cubearr[0][1][1] = new_centre(&blue);
    cubearr[1][1][2] = new_centre(&yellow);

    cubearr[0][0][0] = new_corner(&findcorner(0,0,0));
}
corner& findcorner(int x,int y,int z)
{
    int i=0,j=0;
    corner* corneraddress;
    bool addressfound = false;
    string colors[3] = {"","",""};

    if(z == 0)
    {
        //whiteside;
        if(y == 0)
        {
            //redside
            if(x == 0)
            {
                //blueside
                colors[0] = whiteside[0][0];
                colors[1] = redside[2][0];
                colors[2] = blueside[0][0];
            }
            else
            {
                //greenside
                colors[0] = whiteside[2][0];
                colors[1] = redside[0][0];
                colors[2] = greenside[2][0];
            }
        }
        else
        {
            //orangeside
            if(x == 0)
            {
                //blueside
                colors[0] = whiteside[0][2];
                colors[1] = orangeside[0][0];
                colors[2] = blueside[2][0];
            }
            else
            {
                //greenside
                colors[0] = whiteside[2][2];
                colors[1] = orangeside[2][0];
                colors[2] = greenside[0][0];
            }
        }
    }
    else
    {
        //yellowside;
        if(y == 0)
        {
            //redside
            if(x == 0)
            {
                //blueside
                colors[0] = yellowside[2][0];
                colors[1] = redside[2][2];
                colors[2] = blueside[0][2];
            }
            else
            {
                //greenside
                colors[0] = yellowside[0][0];
                colors[1] = redside[0][2];
                colors[2] = greenside[2][2];
            }
        }
        else
        {
            //orangeside
            if(x == 0)
            {
                //blueside
                colors[0] = yellowside[2][2];
                colors[1] = orangeside[0][2];
                colors[2] = blueside[2][2];
            }
            else
            {
                //greenside
                colors[0] = yellowside[0][2];
                colors[1] = orangeside[2][2];
                colors[2] = greenside[0][2];
            }
        }
    }
    for(i = 0;i < 8;i++)
    {
        if(addressfound)
        {
            break;
        }
        for(j = 0;j < 3;j++)
        {
            if(arr_corners[i].color1 == colors[j])
            {
                if((arr_corners[i].color2 == colors[0]) || (arr_corners[i].color2 == colors[1]) || (arr_corners[i].color2 == colors[2]))
                {
                    if((arr_corners[i].color3 == colors[0]) || (arr_corners[i].color3 == colors[1]) || (arr_corners[i].color3 == colors[2]))
                    {
                        corneraddress = &arr_corners[i];
                        addressfound = true;
                        break;
                    }
                }
            }
        }
    }
    return *corneraddress;
}



bool vaildcolor(string color)
{
    if(color == "white" || color == "red" || color == "green" || color == "orange" || color == "blue"  || color == "yellow")
    {
        return true;
    }
    return false;
}
void inputrules(string color)
{
    if(color == "white")
    {
        cout<<"FACE white\nTOP red\n";
    }
    else if(color == "red")
    {
        cout<<"FACE red\nTOP white\n";
    }
    else if(color == "green")
    {
        cout<<"FACE green\nTOP white\n";
    }
    else if(color == "orange")
    {
        cout<<"FACE orange\nTOP white\n";
    }
    else if(color == "blue")
    {
        cout<<"FACE blue\nTOP white\n";
    }
    else
    {
        cout<<"FACE yellow\nTOP red\n";
    }
}
void doinput()
{
    char dummy;
    system("clear");
    inputrules(whiteside[1][1]);
    cin>>dummy;
    inputside(whiteside);
    system("clear");
    inputrules(redside[1][1]);
    cin>>dummy;
    inputside(redside);
    system("clear");
    inputrules(greenside[1][1]);
    cin>>dummy;
    inputside(greenside);
    system("clear");
    inputrules(orangeside[1][1]);
    cin>>dummy;
    inputside(orangeside);
    system("clear");
    inputrules(blueside[1][1]);
    cin>>dummy;
    inputside(blueside);
    system("clear");
    inputrules(yellowside[1][1]);
    cin>>dummy;
    inputside(yellowside);
}
void inputside(string side[3][3])
{
    int col = 0, row = 0;
    string cellcolor = "";
    for(row = 0;row<3;row++)
    {
        for(col = 0;col<3;col++)
        {
            if(side[col][row] == "")
            {
                displayside(side);
                cout<<"Enter the color of underscored cell\n";
                cin>>cellcolor;
                if(vaildcolor(cellcolor))
                {
                    side[col][row] = cellcolor;
                    displayside(side);
                }
                else
                {
                    col = col - 1;
                }
            }
        }
    }
}

void displayside(string side[3][3])
{
    system("clear");
    int col = 0, row = 0;
    bool notinputting = false;
    for(row = 0;row<3;row++)
    {
        horizontal();
        longspacer();
        for(col = 0;col<3;col++)
        {
            if(side[col][row] == "")
            {
                if(notinputting)
                {
                    spacer();
                }
                else
                {
                    spacerundscr();
                    notinputting = true;
                }
            }
            else
            {
                spacer(side[col][row]);
            }
        }
        cout<<"\n";
        longspacer();
        horizontal();
    }
}

void horizontal()
{
    int i,j;
    for(i = 1;i <= 3;i++)
    {
        for(j = 1;j <= 8;j++)
        {
            cout<<"-";
        }
    }
    cout<<"\n";

}
void longspacer()
{
    int i,j;
    for(i = 1;i <= 3;i++)
    {
        cout<<"|";
        for(j = 1;j <= 6;j++)
        {
            cout<<" ";
        }
        cout<<"|";
    }
    cout<<"\n";
}
void spacer()
{
    int i;
    cout<<"|";
    for(i = 1;i <= 6;i++)
    {
        cout<<" ";
    }
    cout<<"|";
}
void spacerundscr()
{
    int i;
    cout<<"|";
    for(i = 1;i <= 6;i++)
    {
        cout<<"_";
    }
    cout<<"|";
}
void spacer(string color)
{
    cout<<"|";
    if(color == "red")
    {
        cout<<"_"<<color<<"__";
    }
    else if(color == "blue")
    {
        cout<<"_"<<color<<"_";
    }
    else if(color == "green" || color == "white")
    {
        cout<<color<<"_";
    }
    else
    {
        cout<<color;
    }
    cout<<"|";
}


/*
--------
|      |
|yellow|
|      |
--------
*/