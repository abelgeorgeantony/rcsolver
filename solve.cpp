#include<iostream>
#include<stdlib.h>
using namespace std;

struct positionofpiece
{
    int x,y,z;
};
struct edge
{
    const string color1;
    const string color2;
    positionofpiece position;
};

struct corner
{
    const string color1;
    const string color2;
    const string color3;
    positionofpiece position;
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



enum pieces {CORNER,EDGE,CENTRE,core};
typedef struct
{
    int piecetag;
    corner *corner_;
    edge *edge_;
    centre *centre_;
} cube;

void new_corner(corner *piecetoadd,cube *arr_element)
{
    arr_element->piecetag = CORNER;
    arr_element->corner_ = piecetoadd;
}
void new_edge(edge *piecetoadd,cube *arr_element)
{
    arr_element->piecetag = EDGE;
    arr_element->edge_ = piecetoadd;
}
void new_centre(centre *piecetoadd,cube *arr_element)
{
    arr_element->piecetag = CENTRE;
    arr_element->centre_ = piecetoadd;
}

cube cubearr[3][3][3];


void doinput();
void usedefault();
void inputside(string [3][3]);
void displayside(string [3][3]);
void displaycube();
void horizontal();
void spacer();
void spacerundscr();
void longspacer();
void spacer(string);
bool vaildcolor(string);
void connectpieces();
corner& findcorner(int,int,int);
edge& findedge(int,int,int);
void find_missing_edges();
void rotatelayer(char,string);


string whiteside[3][3] = {"","","","","white","","","",""};
string redside[3][3] = {"","","","","red","","","",""};
string greenside[3][3] = {"","","","","green","","","",""};
string orangeside[3][3] = {"","","","","orange","","","",""};
string blueside[3][3] = {"","","","","blue","","","",""};
string yellowside[3][3] = {"","","","","yellow","","","",""};

//char turnlayers[];
//string turndirections[];
cube misplaced[12];
int misplaced_length = 0;

void displaypos()
{
    int col,row,dep;
    for(dep = 0;dep<3;dep++)
    {
        for (row = 0; row < 3; row++)
        {
            for (col = 0; col < 3; col++)
            {
                if(cubearr[col][row][dep].piecetag == core)
                {
                    cout<<"     ";
                    continue;
                }
                if(cubearr[col][row][dep].piecetag == CORNER)
                {
                    cout<<cubearr[col][row][dep].corner_->position.x;
                    cout<<cubearr[col][row][dep].corner_->position.y;
                    cout<<cubearr[col][row][dep].corner_->position.z<<"C ";
                }
                else if(cubearr[col][row][dep].piecetag == EDGE)
                {
                    cout<<cubearr[col][row][dep].edge_->position.x;
                    cout<<cubearr[col][row][dep].edge_->position.y;
                    cout<<cubearr[col][row][dep].edge_->position.z<<"E ";
                }
                else
                {
                    cout<<"CENT ";
                }
            }
            cout<<"\n";
        }
        cout<<"--------------\n";
    }
}

int main()
{
    doinput();
    connectpieces();
    cout<<arr_corners[0].position.x<<"\n";
    cout<<arr_corners[0].position.y<<"\n";
    cout<<arr_corners[0].position.z<<"\n";
    displaycube();
    rotatelayer('U',"clock");
    cout<<arr_corners[0].position.x<<"\n";
    cout<<arr_corners[0].position.y<<"\n";
    cout<<arr_corners[0].position.z<<"\n";
    displaycube();
    return(0);
}



void thecross()
{
    //find_missing_edges();
    
}

void find_missing_edges()
{
    //(1,0) (2,1) (1,2) (0,1)
    int i=0;
    if(cubearr[1][0][0].edge_ != &arr_edges[0])
    {
        new_edge(&arr_edges[0],&misplaced[i]);
        i++;
    }
    if(cubearr[2][1][0].edge_ != &arr_edges[1])
    {
        new_edge(&arr_edges[1],&misplaced[i]);
        i++;
    }
    if(cubearr[1][2][0].edge_ != &arr_edges[2])
    {
        new_edge(&arr_edges[2],&misplaced[i]);
        i++;
    }
    if(cubearr[0][1][0].edge_ != &arr_edges[3])
    {
        new_edge(&arr_edges[3],&misplaced[i]);
        i++;
    }
    misplaced_length = i;
}

void displaycube(){
    //system("clear");
    cout<<"WHITE\n";
    displayside(whiteside);
    cout<<"RED\n";
    displayside(redside);
    cout<<"GREEN\n";
    displayside(greenside);
    cout<<"ORANGE\n";
    displayside(orangeside);
    cout<<"BLUE\n";
    displayside(blueside);
    cout<<"YELLOW\n";
    displayside(yellowside);
}

void rotatelayer(char layertorotate,string direction)
{
    cube tempstorage[2];
    string tempside[3];
    if(layertorotate == 'U')
    {
        if(direction == "clock")
        {
            tempstorage[0]=cubearr[0][0][0];
            tempstorage[1]=cubearr[1][0][0];

            cubearr[0][0][0] = cubearr[2][0][0];
            cubearr[1][0][0] = cubearr[2][0][1];
            cubearr[2][0][0] = cubearr[2][0][2];
            cubearr[2][0][1] = cubearr[1][0][2];
            cubearr[2][0][2] = cubearr[0][0][2];
            cubearr[1][0][2] = cubearr[0][0][1];
            cubearr[0][0][2] = tempstorage[0];
            cubearr[0][0][1] = tempstorage[1];
            ////////////////////////////////////
            tempside[0] = whiteside[0][0];
            tempside[1] = whiteside[1][0];
            tempside[2] = whiteside[2][0];
            whiteside[0][0] = greenside[2][0];
            whiteside[1][0] = greenside[2][1];
            whiteside[2][0] = greenside[2][2];
            greenside[2][0] = yellowside[0][0];
            greenside[2][1] = yellowside[1][0];
            greenside[2][2] = yellowside[2][0];
            yellowside[0][0] = blueside[0][2];
            yellowside[1][0] = blueside[0][1];
            yellowside[2][0] = blueside[0][0];
            blueside[0][2] = tempside[0];
            blueside[0][1] = tempside[1];
            blueside[0][0] = tempside[2];
            tempside[0] = redside[2][0];
            tempside[1] = redside[1][0];
            redside[2][0] = redside[0][0];
            redside[1][0] = redside[0][1];
            redside[0][0] = redside[0][2];
            redside[0][1] = redside[1][2];
            redside[0][2] = redside[2][2];
            redside[1][2] = redside[2][1];
            redside[2][2] = tempside[0];
            redside[2][1] = tempside[1];
        }
        else
        {
            tempstorage[0]=cubearr[2][0][0];
            tempstorage[1]=cubearr[1][0][0];

            cubearr[2][0][0] = cubearr[0][0][0];
            cubearr[1][0][0] = cubearr[0][0][1];
            cubearr[0][0][0] = cubearr[0][0][2];
            cubearr[0][0][1] = cubearr[1][0][2];
            cubearr[0][0][2] = cubearr[2][0][2];
            cubearr[1][0][2] = cubearr[2][0][1];
            cubearr[2][0][2] = tempstorage[0];
            cubearr[2][0][1] = tempstorage[1];
            ////////////////////////////////////
            tempside[0] = whiteside[2][0];
            tempside[1] = whiteside[1][0];
            tempside[2] = whiteside[0][0];
            whiteside[2][0] = blueside[0][0];
            whiteside[1][0] = blueside[0][1];
            whiteside[0][0] = blueside[0][2];
            blueside[0][0] = yellowside[2][0];
            blueside[0][1] = yellowside[1][0];
            blueside[0][2] = yellowside[0][0];
            yellowside[2][0] = greenside[2][2];
            yellowside[1][0] = greenside[2][1];
            yellowside[0][0] = greenside[2][0];
            greenside[2][2] = tempside[0];
            greenside[2][1] = tempside[1];
            greenside[2][0] = tempside[2];
            tempside[0] = redside[0][0];
            tempside[1] = redside[1][0];
            redside[0][0] = redside[2][0];
            redside[1][0] = redside[2][1];
            redside[2][0] = redside[2][2];
            redside[2][1] = redside[1][2];
            redside[2][2] = redside[0][2];
            redside[1][2] = redside[0][1];
            redside[0][2] = tempside[0];
            redside[0][1] = tempside[1];
        }
    }
    else if(layertorotate == 'D')
    {
        if(direction == "clock")
        {
            tempstorage[0]=cubearr[2][2][0];
            tempstorage[1]=cubearr[1][2][0];

            cubearr[2][2][0] = cubearr[0][2][0];
            cubearr[1][2][0] = cubearr[0][2][1];
            cubearr[0][2][0] = cubearr[0][2][2];
            cubearr[0][2][1] = cubearr[1][2][2];
            cubearr[0][2][2] = cubearr[2][2][2];
            cubearr[1][2][2] = cubearr[2][2][1];
            cubearr[2][2][2] = tempstorage[0];
            cubearr[2][2][1] = tempstorage[1];
            ////////////////////////////////////
            tempside[0] = whiteside[2][2];
            tempside[1] = whiteside[1][2];
            tempside[2] = whiteside[0][2];
            whiteside[2][2] = blueside[2][0];
            whiteside[1][2] = blueside[2][1];
            whiteside[0][2] = blueside[2][2];
            blueside[2][0] = yellowside[2][2];
            blueside[2][1] = yellowside[1][2];
            blueside[2][2] = yellowside[0][2];
            yellowside[2][2] = greenside[0][2];
            yellowside[1][2] = greenside[0][1];
            yellowside[0][2] = greenside[0][0];
            greenside[0][2] = tempside[0];
            greenside[0][1] = tempside[1];
            greenside[0][0] = tempside[2];
            tempside[0] = orangeside[2][0];
            tempside[1] = orangeside[1][0];
            orangeside[2][0] = orangeside[0][0];
            orangeside[1][0] = orangeside[0][1];
            orangeside[0][0] = orangeside[0][2];
            orangeside[0][1] = orangeside[1][2];
            orangeside[0][2] = orangeside[2][2];
            orangeside[1][2] = orangeside[2][1];
            orangeside[2][2] = tempside[0];
            orangeside[2][1] = tempside[1];
        }
        else
        {
            tempstorage[0]=cubearr[0][2][0];
            tempstorage[1]=cubearr[1][2][0];

            cubearr[0][2][0] = cubearr[2][2][0];
            cubearr[1][2][0] = cubearr[2][2][1];
            cubearr[2][2][0] = cubearr[2][2][2];
            cubearr[2][2][1] = cubearr[1][2][2];
            cubearr[2][2][2] = cubearr[0][2][2];
            cubearr[1][2][2] = cubearr[0][2][1];
            cubearr[0][2][2] = tempstorage[0];
            cubearr[0][2][1] = tempstorage[1];
            ////////////////////////////////////
            tempside[0] = whiteside[0][2];
            tempside[1] = whiteside[1][2];
            tempside[2] = whiteside[2][2];
            whiteside[0][2] = greenside[0][0];
            whiteside[1][2] = greenside[0][1];
            whiteside[2][2] = greenside[0][2];
            greenside[0][0] = yellowside[0][2];
            greenside[0][1] = yellowside[1][2];
            greenside[0][2] = yellowside[2][2];
            yellowside[0][2] = blueside[2][2];
            yellowside[1][2] = blueside[2][1];
            yellowside[2][2] = blueside[2][0];
            blueside[2][2] = tempside[0];
            blueside[2][1] = tempside[1];
            blueside[2][0] = tempside[2];
            tempside[0] = orangeside[0][0];
            tempside[1] = orangeside[1][0];
            orangeside[0][0] = orangeside[2][0];
            orangeside[1][0] = orangeside[2][1];
            orangeside[2][0] = orangeside[2][2];
            orangeside[2][1] = orangeside[1][2];
            orangeside[2][2] = orangeside[0][2];
            orangeside[1][2] = orangeside[0][1];
            orangeside[0][2] = tempside[0];
            orangeside[0][1] = tempside[1];
        }
    }
    else if(layertorotate == 'L')
    {
        if(direction == "clock")
        {
            tempstorage[0]=cubearr[0][2][0];
            tempstorage[1]=cubearr[0][1][0];

            cubearr[0][2][0] = cubearr[0][0][0];
            cubearr[0][1][0] = cubearr[0][0][1];
            cubearr[0][0][0] = cubearr[0][0][2];
            cubearr[0][0][1] = cubearr[0][1][2];
            cubearr[0][0][2] = cubearr[0][2][2];
            cubearr[0][1][2] = cubearr[0][2][1];
            cubearr[0][2][2] = tempstorage[0];
            cubearr[0][2][1] = tempstorage[1];
            ////////////////////////////////////
            tempside[0] = whiteside[0][2];
            tempside[1] = whiteside[0][1];
            tempside[2] = whiteside[0][0];
            whiteside[0][2] = redside[2][0];
            whiteside[0][1] = redside[2][1];
            whiteside[0][0] = redside[2][2];
            redside[2][0] = yellowside[2][0];
            redside[2][1] = yellowside[2][1];
            redside[2][2] = yellowside[2][2];
            yellowside[2][0] = orangeside[0][2];
            yellowside[2][1] = orangeside[0][1];
            yellowside[2][2] = orangeside[0][0];
            orangeside[0][2] = tempside[0];
            orangeside[0][1] = tempside[1];
            orangeside[0][0] = tempside[2];
            tempside[0] = blueside[2][0];
            tempside[1] = blueside[1][0];
            blueside[2][0] = blueside[0][0];
            blueside[1][0] = blueside[0][1];
            blueside[0][0] = blueside[0][2];
            blueside[0][1] = blueside[1][2];
            blueside[0][2] = blueside[2][2];
            blueside[1][2] = blueside[2][1];
            blueside[2][2] = tempside[0];
            blueside[2][1] = tempside[1];
        }
        else
        {
            tempstorage[0]=cubearr[0][0][0];
            tempstorage[1]=cubearr[0][1][0];

            cubearr[0][0][0] = cubearr[0][2][0];
            cubearr[0][1][0] = cubearr[0][2][1];
            cubearr[0][2][0] = cubearr[0][2][2];
            cubearr[0][2][1] = cubearr[0][1][2];
            cubearr[0][2][2] = cubearr[0][0][2];
            cubearr[0][1][2] = cubearr[0][0][1];
            cubearr[0][0][2] = tempstorage[0];
            cubearr[0][0][1] = tempstorage[1];
            ////////////////////////////////////
            tempside[0] = whiteside[0][0];
            tempside[1] = whiteside[0][1];
            tempside[2] = whiteside[0][2];
            whiteside[0][0] = orangeside[0][0];
            whiteside[0][1] = orangeside[0][1];
            whiteside[0][2] = orangeside[0][2];
            orangeside[0][0] = yellowside[2][2];
            orangeside[0][1] = yellowside[2][1];
            orangeside[0][2] = yellowside[2][0];
            yellowside[2][2] = redside[2][2];
            yellowside[2][1] = redside[2][1];
            yellowside[2][0] = redside[2][0];
            redside[2][2] = tempside[0];
            redside[2][1] = tempside[1];
            redside[2][0] = tempside[2];
            tempside[0] = blueside[0][0];
            tempside[1] = blueside[1][0];
            blueside[0][0] = blueside[2][0];
            blueside[1][0] = blueside[2][1];
            blueside[2][0] = blueside[2][2];
            blueside[2][1] = blueside[1][2];
            blueside[2][2] = blueside[0][2];
            blueside[1][2] = blueside[0][1];
            blueside[0][2] = tempside[0];
            blueside[0][1] = tempside[1];
        }
    }
    else if(layertorotate == 'R')
    {
        if(direction == "clock")
        {
            tempstorage[0]=cubearr[2][0][0];
            tempstorage[1]=cubearr[2][1][0];

            cubearr[2][0][0] = cubearr[2][2][0];
            cubearr[2][1][0] = cubearr[2][2][1];
            cubearr[2][2][0] = cubearr[2][2][2];
            cubearr[2][2][1] = cubearr[2][1][2];
            cubearr[2][2][2] = cubearr[2][0][2];
            cubearr[2][1][2] = cubearr[2][0][1];
            cubearr[2][0][2] = tempstorage[0];
            cubearr[2][0][1] = tempstorage[1];
            ////////////////////////////////////
            tempside[0] = whiteside[2][0];
            tempside[1] = whiteside[2][1];
            tempside[2] = whiteside[2][2];
            whiteside[2][0] = orangeside[2][0];
            whiteside[2][1] = orangeside[2][1];
            whiteside[2][2] = orangeside[2][2];
            orangeside[2][0] = yellowside[0][2];
            orangeside[2][1] = yellowside[0][1];
            orangeside[2][2] = yellowside[0][0];
            yellowside[0][2] = redside[0][2];
            yellowside[0][1] = redside[0][1];
            yellowside[0][0] = redside[0][0];
            redside[0][2] = tempside[0];
            redside[0][1] = tempside[1];
            redside[0][0] = tempside[2];
            tempside[0] = greenside[2][0];
            tempside[1] = greenside[1][0];
            greenside[2][0] = greenside[0][0];
            greenside[1][0] = greenside[0][1];
            greenside[0][0] = greenside[0][2];
            greenside[0][1] = greenside[1][2];
            greenside[0][2] = greenside[2][2];
            greenside[1][2] = greenside[2][1];
            greenside[2][2] = tempside[0];
            greenside[2][1] = tempside[1];
        }
        else
        {
            tempstorage[0]=cubearr[2][2][0];
            tempstorage[1]=cubearr[2][1][0];

            cubearr[2][2][0] = cubearr[2][0][0];
            cubearr[2][1][0] = cubearr[2][0][1];
            cubearr[2][0][0] = cubearr[2][0][2];
            cubearr[2][0][1] = cubearr[2][1][2];
            cubearr[2][0][2] = cubearr[2][2][2];
            cubearr[2][1][2] = cubearr[2][2][1];
            cubearr[2][2][2] = tempstorage[0];
            cubearr[2][2][1] = tempstorage[1];
            ////////////////////////////////////
            tempside[0] = whiteside[2][2];
            tempside[1] = whiteside[2][1];
            tempside[2] = whiteside[2][0];
            whiteside[2][2] = redside[0][0];
            whiteside[2][1] = redside[0][1];
            whiteside[2][0] = redside[0][2];
            redside[0][0] = yellowside[0][0];
            redside[0][1] = yellowside[0][1];
            redside[0][2] = yellowside[0][2];
            yellowside[0][0] = orangeside[2][2];
            yellowside[0][1] = orangeside[2][1];
            yellowside[0][2] = orangeside[2][0];
            orangeside[2][2] = tempside[0];
            orangeside[2][1] = tempside[1];
            orangeside[2][0] = tempside[2];
            tempside[0] = greenside[0][0];
            tempside[1] = greenside[1][0];
            greenside[0][0] = greenside[2][0];
            greenside[1][0] = greenside[2][1];
            greenside[2][0] = greenside[2][2];
            greenside[2][1] = greenside[1][2];
            greenside[2][2] = greenside[0][2];
            greenside[1][2] = greenside[0][1];
            greenside[0][2] = tempside[0];
            greenside[0][1] = tempside[1];
        }
    }
    else if(layertorotate == 'F')
    {
        if(direction == "clock")
        {
            tempstorage[0]=cubearr[2][0][0];
            tempstorage[1]=cubearr[1][0][0];

            cubearr[2][0][0] = cubearr[0][0][0];
            cubearr[1][0][0] = cubearr[0][1][0];
            cubearr[0][0][0] = cubearr[0][2][0];
            cubearr[0][1][0] = cubearr[1][2][0];
            cubearr[0][2][0] = cubearr[2][2][0];
            cubearr[1][2][0] = cubearr[2][1][0];
            cubearr[2][2][0] = tempstorage[0];
            cubearr[2][1][0] = tempstorage[1];
            ////////////////////////////////////
            tempside[0] = redside[0][0];
            tempside[1] = redside[1][0];
            tempside[2] = redside[2][0];
            redside[0][0] = blueside[0][0];
            redside[1][0] = blueside[1][0];
            redside[2][0] = blueside[2][0];
            blueside[0][0] = orangeside[0][0];
            blueside[1][0] = orangeside[1][0];
            blueside[2][0] = orangeside[2][0];
            orangeside[0][0] = greenside[0][0];
            orangeside[1][0] = greenside[1][0];
            orangeside[2][0] = greenside[2][0];
            greenside[0][0] = tempside[0];
            greenside[1][0] = tempside[1];
            greenside[2][0] = tempside[2];
            tempside[0] = whiteside[2][0];
            tempside[1] = whiteside[1][0];
            whiteside[2][0] = whiteside[0][0];
            whiteside[1][0] = whiteside[0][1];
            whiteside[0][0] = whiteside[0][2];
            whiteside[0][1] = whiteside[1][2];
            whiteside[0][2] = whiteside[2][2];
            whiteside[1][2] = whiteside[2][1];
            whiteside[2][2] = tempside[0];
            whiteside[2][1] = tempside[1];
        }
        else
        {
            tempstorage[0]=cubearr[0][0][0];
            tempstorage[1]=cubearr[1][0][0];

            cubearr[0][0][0] = cubearr[2][0][0];
            cubearr[1][0][0] = cubearr[2][1][0];
            cubearr[2][0][0] = cubearr[2][2][0];
            cubearr[2][1][0] = cubearr[1][2][0];
            cubearr[2][2][0] = cubearr[0][2][0];
            cubearr[1][2][0] = cubearr[0][1][0];
            cubearr[0][2][0] = tempstorage[0];
            cubearr[0][1][0] = tempstorage[1];
            ////////////////////////////////////
            tempside[0] = redside[2][0];
            tempside[1] = redside[1][0];
            tempside[2] = redside[0][0];
            redside[2][0] = greenside[2][0];
            redside[1][0] = greenside[1][0];
            redside[0][0] = greenside[0][0];
            greenside[2][0] = orangeside[2][0];
            greenside[1][0] = orangeside[1][0];
            greenside[0][0] = orangeside[0][0];
            orangeside[2][0] = blueside[2][0];
            orangeside[1][0] = blueside[1][0];
            orangeside[0][0] = blueside[0][0];
            blueside[2][0] = tempside[0];
            blueside[1][0] = tempside[1];
            blueside[0][0] = tempside[2];
            tempside[0] = whiteside[0][0];
            tempside[1] = whiteside[1][0];
            whiteside[0][0] = whiteside[2][0];
            whiteside[1][0] = whiteside[2][1];
            whiteside[2][0] = whiteside[2][2];
            whiteside[2][1] = whiteside[1][2];
            whiteside[2][2] = whiteside[0][2];
            whiteside[1][2] = whiteside[0][1];
            whiteside[0][2] = tempside[0];
            whiteside[0][1] = tempside[1];
        }
    }
    else if(layertorotate == 'B')
    {
        if(direction == "clock")
        {
            tempstorage[0]=cubearr[0][0][2];
            tempstorage[1]=cubearr[1][0][2];

            cubearr[0][0][2] = cubearr[2][0][2];
            cubearr[1][0][2] = cubearr[2][1][2];
            cubearr[2][0][2] = cubearr[2][2][2];
            cubearr[2][1][2] = cubearr[1][2][2];
            cubearr[2][2][2] = cubearr[0][2][2];
            cubearr[1][2][2] = cubearr[0][1][2];
            cubearr[0][2][2] = tempstorage[0];
            cubearr[0][1][2] = tempstorage[1];
            ////////////////////////////////////
            tempside[0] = redside[2][0];
            tempside[1] = redside[1][0];
            tempside[2] = redside[0][0];
            redside[2][0] = greenside[2][0];
            redside[1][0] = greenside[1][0];
            redside[0][0] = greenside[0][0];
            greenside[2][0] = orangeside[2][0];
            greenside[1][0] = orangeside[1][0];
            greenside[0][0] = orangeside[0][0];
            orangeside[2][0] = blueside[2][0];
            orangeside[1][0] = blueside[1][0];
            orangeside[0][0] = blueside[0][0];
            blueside[2][0] = tempside[0];
            blueside[1][0] = tempside[1];
            blueside[0][0] = tempside[2];
            tempside[0] = yellowside[2][0];
            tempside[1] = yellowside[1][0];
            yellowside[2][0] = yellowside[0][0];
            yellowside[1][0] = yellowside[0][1];
            yellowside[0][0] = yellowside[0][2];
            yellowside[0][1] = yellowside[1][2];
            yellowside[0][2] = yellowside[2][2];
            yellowside[1][2] = yellowside[2][1];
            yellowside[2][2] = tempside[0];
            yellowside[2][1] = tempside[1];
        }
        else
        {
            tempstorage[0]=cubearr[2][0][2];
            tempstorage[1]=cubearr[1][0][2];

            cubearr[2][0][2] = cubearr[0][0][2];
            cubearr[1][0][2] = cubearr[0][1][2];
            cubearr[0][0][2] = cubearr[0][2][2];
            cubearr[0][1][2] = cubearr[1][2][2];
            cubearr[0][2][2] = cubearr[2][2][2];
            cubearr[1][2][2] = cubearr[2][1][2];
            cubearr[2][2][0] = tempstorage[0];
            cubearr[2][1][0] = tempstorage[1];
            ////////////////////////////////////
            tempside[0] = redside[0][0];
            tempside[1] = redside[1][0];
            tempside[2] = redside[2][0];
            redside[0][0] = blueside[0][0];
            redside[1][0] = blueside[1][0];
            redside[2][0] = blueside[2][0];
            blueside[0][0] = orangeside[0][0];
            blueside[1][0] = orangeside[1][0];
            blueside[2][0] = orangeside[2][0];
            orangeside[0][0] = greenside[0][0];
            orangeside[1][0] = greenside[1][0];
            orangeside[2][0] = greenside[2][0];
            greenside[0][0] = tempside[0];
            greenside[1][0] = tempside[1];
            greenside[2][0] = tempside[2];
            tempside[0] = yellowside[0][0];
            tempside[1] = yellowside[1][0];
            yellowside[0][0] = yellowside[2][0];
            yellowside[1][0] = yellowside[2][1];
            yellowside[2][0] = yellowside[2][2];
            yellowside[2][1] = yellowside[1][2];
            yellowside[2][2] = yellowside[0][2];
            yellowside[1][2] = yellowside[0][1];
            yellowside[0][2] = tempside[0];
            yellowside[0][1] = tempside[1];
        }
    }
    else
    {
        throw;
    }
    connectpieces();
}


void connectpieces()
{
    cubearr[1][1][1].piecetag = core; // core of the cube!

    new_centre(&white,&cubearr[1][1][0]);
    new_centre(&red,&cubearr[1][0][1]);
    new_centre(&green,&cubearr[2][1][1]);
    new_centre(&orange,&cubearr[1][2][1]);
    new_centre(&blue,&cubearr[0][1][1]);
    new_centre(&yellow,&cubearr[1][1][2]);

    new_corner(&findcorner(0,0,0),&cubearr[0][0][0]);
    new_corner(&findcorner(2,0,0),&cubearr[2][0][0]);
    new_corner(&findcorner(0,2,0),&cubearr[0][2][0]);
    new_corner(&findcorner(2,2,0),&cubearr[2][2][0]);
    new_corner(&findcorner(0,0,2),&cubearr[0][0][2]);
    new_corner(&findcorner(2,0,2),&cubearr[2][0][2]);
    new_corner(&findcorner(0,2,2),&cubearr[0][2][2]);
    new_corner(&findcorner(2,2,2),&cubearr[2][2][2]);

    new_edge(&findedge(1,0,0),&cubearr[1][0][0]);
    new_edge(&findedge(1,2,0),&cubearr[1][2][0]);
    new_edge(&findedge(0,1,0),&cubearr[0][1][0]);
    new_edge(&findedge(2,1,0),&cubearr[2][1][0]);
    new_edge(&findedge(0,0,1),&cubearr[0][0][1]);
    new_edge(&findedge(2,0,1),&cubearr[2][0][1]);
    new_edge(&findedge(0,2,1),&cubearr[0][2][1]);
    new_edge(&findedge(2,2,1),&cubearr[2][2][1]);
    new_edge(&findedge(1,0,2),&cubearr[1][0][2]);
    new_edge(&findedge(1,2,2),&cubearr[1][2][2]);
    new_edge(&findedge(0,1,2),&cubearr[0][1][2]);
    new_edge(&findedge(2,1,2),&cubearr[2][1][2]);
}
corner& findcorner(int x,int y,int z)
{
    int i=0,j=0;
    corner* corneraddress;
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
        for(j = 0;j < 3;j++)
        {
            if(arr_corners[i].color1 == colors[j])
            {
                if((arr_corners[i].color2 == colors[0]) || (arr_corners[i].color2 == colors[1]) || (arr_corners[i].color2 == colors[2]))
                {
                    if((arr_corners[i].color3 == colors[0]) || (arr_corners[i].color3 == colors[1]) || (arr_corners[i].color3 == colors[2]))
                    {
                        corneraddress = &arr_corners[i];
                        corneraddress->position.x = x;
                        corneraddress->position.y = y;
                        corneraddress->position.z = z;
                        return *corneraddress;
                    }
                }
            }
        }
    }
    throw;
}
edge& findedge(int x,int y,int z)
{
    int i=0,j=0;
    edge* edgeaddress;
    string colors[2] = {"",""};

    if(z == 0)
    {
        //whiteside
        if(y == 0)
        {
            //redside
            colors[0] = whiteside[1][0];
            colors[1] = redside[1][0];
        }
        else if(y == 2)
        {
            //orangeside
            colors[0] = whiteside[1][2];
            colors[1] = orangeside[1][0];
        }
        else
        {
            //blueside,greenside
            if(x == 0)
            {
                //blueside
                colors[0] = whiteside[0][1];
                colors[1] = blueside[1][0];
            }
            else
            {
                //greenside
                colors[0] = whiteside[2][1];
                colors[1] = greenside[1][0];
            }
        }
    }
    else if(z == 2)
    {
        //yellowside
        if(y == 0)
        {
            //redside
            colors[0] = yellowside[1][0];
            colors[1] = redside[1][2];
        }
        else if(y == 2)
        {
            //orangeside
            colors[0] = yellowside[1][2];
            colors[1] = orangeside[1][2];
        }
        else
        {
            //blueside,greenside
            if(x == 0)
            {
                //blueside
                colors[0] = yellowside[2][1];
                colors[1] = blueside[1][2];
            }
            else
            {
                //greenside
                colors[0] = yellowside[0][1];
                colors[1] = greenside[1][2];
            }
        }
    }
    else
    {
        //redside,blueside,orangeside,greenside
        if(y == 0)
        {
            //redside confirmed
            //blueside,greenside
            if(x == 0)
            {
                //blueside
                colors[0] = redside[2][1];
                colors[1] = blueside[0][1];
            }
            else
            {
                //greenside
                colors[0] = redside[0][1];
                colors[1] = greenside[2][1];
            }
        }
        else
        {
            //orangeside confirmed
            //blueside,greenside
            if(x == 0)
            {
                //blueside
                colors[0] = orangeside[0][1];
                colors[1] = blueside[2][1];
            }
            else
            {
                //greenside
                colors[0] = orangeside[2][1];
                colors[1] = greenside[0][1];
            }
        }
    }

    for(i = 0;i < 12;i++)
    {
        for(j = 0;j < 2;j++)
        {
            if(arr_edges[i].color1 == colors[j])
            {
                if((arr_edges[i].color2 == colors[0]) || (arr_edges[i].color2 == colors[1]))
                {
                    edgeaddress = &arr_edges[i];
                    edgeaddress->position.x = x;
                    edgeaddress->position.y = y;
                    edgeaddress->position.z = z;
                    return *edgeaddress;
                }
            }
        }
    }
    throw;
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
    cout<<"do you want to use default solved cube?\ninput y for yes\nOR\ninput n for no (asks for colors)\n";
    cin>>dummy;
    if(dummy == 'y')
    {
        usedefault();
        return;
    }
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
void usedefault()
{
    int row,col;
    for(row = 0;row<3;row++)
    {
        for(col = 0;col<3;col++)
        {
            whiteside[col][row] = "white";
            redside[col][row] = "red";
            greenside[col][row] = "green";
            orangeside[col][row] = "orange";
            blueside[col][row] = "blue";
            yellowside[col][row] = "yellow";
        }
    }
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
                system("clear");
                displayside(side);
                cout<<"Enter the color of underscored cell\n";
                cin>>cellcolor;
                if(vaildcolor(cellcolor))
                {
                    side[col][row] = cellcolor;
                    system("clear");
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