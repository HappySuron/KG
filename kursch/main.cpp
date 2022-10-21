#include <iostream>
#include <graphics.h>
#include <winbgim.h>
#include <conio.h>
#include <cmath>


/*----------------------------------Some-stupid-commentaries----------------------------------

** INP - stands for in progress, things should be done
** HTC - here to change Some things, written upper then tag, should be done

**  In define A is for piramid with 4 corners in the base
    For 3 corners stands letter B  &&                                                          --INP


**  For functions we cant use the same functions cause HP[AN][AM] != HP[BN][BM] 5!=4 corners
    So for functions which can be used only for A it will seem like "void moving_A"
    for B "moving_B"                                                                           --INP

**  Also  it is needed to be multiplied matrix with dif [][], so "multing_1(HelperMatrix, MULT)"
    with index it will be checked what we will need to do
    1 - 5 and 4 for A
    2 - 4 and 4 for B
    3 - ...                                                                                    --INP

**  BTW the coords starts in up-left corner, which is not good cause, we cant  see the shadow
    so all the coords are counted in normal way, but when it is drawn, we add 300 to move
    the 000 point in the center of the screen. Hope it will not break
-------------------------------------------------------------------------------------------*/


#define AX0 40
#define AY0 -40
#define AZ0 60

#define AX1 20
#define AY1 -20
#define AZ1 20

#define AX2 60
#define AY2 -20
#define AZ2 20

#define AX3 60
#define AY3 -60
#define AZ3 20

#define AX4 20
#define AY4 -60
#define AZ4 20


#define BX0 80
#define BY0 -80
#define BZ0 120

#define BX1 40
#define BY1 -40
#define BZ1 40

#define BX2 120
#define BY2 -40
#define BZ2 40

#define BX3 120
#define BY3 -120
#define BZ3 40


#define DX 5  // Just for moving delta
#define DY 5
#define DZ 5


#define UG M_PI/6   // koof for rotation increase
#define INC 1.4     // or decrease
#define DEC 0.8

const int AN =5;       // N - amount of conors
const int AM =4;        // M - x,y,z,1

const int BN = 4;
const int BM = 4;

float AXC, AYC, AZC;    // kvazi-Center
float BXC, BYC, BZC;


using namespace std;

float PROJECTION[AM][AM] =
    {{0.7, -0.4, 0, 0},
    {0, 0.8, 0, 0},
    {-0.7, -0.4, 1, 0},
    {0, 0, 0, 1}};          // The matrix of the projection In this case izometria, at least seems to be

    int AB=0; // this is the flag to see what figure we are working with right now

//----------------functions----------------------

void Draw_Figure_Both(float HPA[AN][AM], float HPB[BN][BM]);
void Draw_FigureA(float HP[AN][AM]);
void Draw_FigureB(float HP[BN][BM]);


void Draw_Polly(); // to draw the floor, where shadow should be



void multing_1(float HP[AN][AM], float Mult[AM][AM]);
void multing_2(float HP[AM][AM], float Mult[AM][AM]); // Not sure that AM is correct to be used here maybe to change


void find_center_A(float HPA[AN][AM]);
void find_center_B(float HPB[BN][BM]);

void moving_A(float HPA[AN][AM], float dx, float dy, float dz);
void moving_B(float HPB[BN][BM], float dx, float dy, float dz);
void moving(float HPA[AN][AM], float HPB[BN][BM], float dx, float dy, float dz);                       // Here should be two arguments (float HPA[][], HPB[][])
                                                                                    // Here should be moving_B
                                                                                    // HTC



void rotating_A(float HPA[AN][AM], float angle, int index);
// Here index for
// 1 - x
// 2 - y
// 3 - z
//-----------------------------------------------

void increese_decreese_A(float HPA[AN][AM], float K);

//void find_normals_A(float HP[AN][AM], float NRM[4][5]);

float NORMALS[4][5];
float LIGHT = (0, 1000, 0, 1);
float CAMERA = (0,0, 500, 1);

int main(){
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");

    setcolor(BLACK);                    // Just some pre-things
    setfillstyle(SOLID_FILL,WHITE);     // To make sure its white
    bar(0,0,640,480);                   //


    float AFG[AN][AM] = {{AX0,AY0,AZ0, 1}, {AX1,AY1,AZ1, 1}, {AX2,AY2,AZ2, 1},{AX3,AY3,AZ3, 1},{AX4,AY4,AZ4, 1}};
    float BFG[BN][BM] = {{BX0, BY0, BZ0, 1}, {BX1, BY1, BZ1, 1}, {BX2, BY2, BZ2, 1}, {BX3, BY3, BZ3, 1}};

    /* to check the koords
    cout << AX1 << " " << AY1 << " " << AZ1 << endl;
    cout << AX2 << " " << AY2 << " " << AZ2 << endl;
    cout << AX3 << " " << AY3 << " " << AZ3 << endl;
    cout << AX4 << " " << AY4 << " " << AZ4 << endl;
    cout << AX0 << " " << AY0 << " " << AZ0 << endl;
    */





    char c;
    //find_normals_A(AFG, NORMALS);
    while(true){

        c = _getch();
        try{
        switch (c){
            case 'w':  {moving(AFG, BFG, 0, -DY,0);
                        break;}
            case 'a':  {moving(AFG, BFG, -DX, 0,0);
                        break;}
            case 's':  {moving(AFG, BFG, 0, DY, 0);
                        break;}
            case 'd':  {moving(AFG, BFG, DX, 0,0);
                        break;}
                        case 'q':  {moving(AFG, BFG, 0, 0, DZ);
                        break;}
            case 'e':  {moving(AFG, BFG, 0, 0, -DZ);
                        break;}
            case 'o':  {rotating_A(AFG, UG, 1);
                        break;}
            case 'u':  {rotating_A(AFG, -UG, 1);
                        break;}
            case 'i':  {rotating_A(AFG, UG, 2);
                        break;}
            case 'k':  {rotating_A(AFG, -UG, 2);
                        break;}
            case 'j':  {rotating_A(AFG, UG, 3);
                        break;}
            case 'l':  {rotating_A(AFG, -UG, 3);
                        break;}
            case 'z':  {increese_decreese_A(AFG, INC);
                        break;}
            case 'c':  {increese_decreese_A(AFG, DEC);
                        break;}
            case '1': { AB=0;
                        break;};
            case '2': { AB=1;
                        break;}
        }
        setcolor(BLACK);
        setfillstyle(SOLID_FILL,WHITE);
        bar(0,0,640,480);
        Draw_Figure_Both(AFG, BFG);
        }catch (char const* err){
         cout << err;
        }
    }
    getch();
    closegraph();
}


//----------------------------------------------------------------------------
//============================Functions of drawing============================
//============================Functions of drawing============================
//----------------------------------------------------------------------------
void Draw_Figure_Both(float HPA[AN][AM], float HPB[BN][BM]){
    Draw_Polly(); // draw the floor, so she can hit it
// It is need to be if there will be any checks
    for (int i =0; i <AN; i++){
        if (HPA[i][1] >=0) throw "under";
    }
     // to check the koords
    for (int i =0; i <BN; i++){
        if (HPB[i][1] >=0) throw "under";
    }
    Draw_FigureA(HPA);
    Draw_FigureB(HPB);
}


void Draw_FigureA(float HP[AN][AM]){


    float TDO[AN][AM]; // TecnicallyDrawingOne

    for (int i = 0; i < AN; i++)
    {
        for (int j = 0; j < AM; j++)
        {
            TDO[i][j] = HP[i][j];
        }
    }
    multing_1(TDO , PROJECTION);
    for (int i=1; i < AN-1; i++){
        line (round(TDO[i][0])+300, round(TDO[i][1])+300, round(TDO[i+1][0])+300, round(TDO[i+1][1])+300);
    }
    line (round(TDO[1][0])+300, round(TDO[1][1])+300, round(TDO[AN-1][0])+300, round(TDO[AN-1][1])+300);

    for (int i=1; i < AN; i++){
        line (round(TDO[i][0])+300, round(TDO[i][1])+300, round(TDO[0][0])+300, round(TDO[0][1])+300);
    }
}

void Draw_FigureB(float HP[BN][BM]){


    float TDO[BN][BM]; // TecnicallyDrawingOne

    for (int i = 0; i < BN; i++)
    {
        for (int j = 0; j < BM; j++)
        {
            TDO[i][j] = HP[i][j];
        }
    }
    multing_1(TDO , PROJECTION);
    for (int i=1; i < BN-1; i++){
        line (round(TDO[i][0])+300, round(TDO[i][1])+300, round(TDO[i+1][0])+300, round(TDO[i+1][1])+300);
    }
    line (round(TDO[1][0])+300, round(TDO[1][1])+300, round(TDO[BN-1][0])+300, round(TDO[BN-1][1])+300);

    for (int i=1; i < BN; i++){
        line (round(TDO[i][0])+300, round(TDO[i][1])+300, round(TDO[0][0])+300, round(TDO[0][1])+300);
    }
}


void Draw_Polly(){

    // to draw the floor, where shadow should be

    float Polly[4][4] =
    {{-300,0,-300,1},
    {300,0,-300,1},
    {300,0,300,1},
    {-300,0,300,1}}; // this is the square

    multing_2(Polly, PROJECTION);
/*
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++)
        {
            cout << Polly[i][j] << " ";
        }
            cout <<endl;
    }
        */

    int poly[10];                           // | Draw the figure
    poly[0] = Polly[0][0]+300;              // | the square
    poly[1] = Polly[0][1]+300;              // | before fillpoly make it
                                            // V look good
    poly[2] = Polly[1][0]+300;
    poly[3] = Polly[1][1]+300;

    poly[4] = Polly[2][0]+300;
    poly[5] = Polly[2][1]+300;

    poly[6] = Polly[3][0]+300;
    poly[7] = Polly[3][1]+300;

    poly[8] = poly[0];
    poly[9] = poly[1];


    setfillstyle(HATCH_FILL,YELLOW);
    setcolor(RED);
    setbkcolor(WHITE);
    fillpoly(5,poly);

    setcolor(BLACK);
    setfillstyle(SOLID_FILL,WHITE);

}

//----------------------------------------------------------------------------
//============================================================================
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
//===============================Functions of multiplying=====================
//----------------------------------------------------------------------------
void multing_1(float HP[AN][AM], float Mult[AM][AM])
{
    float res[AN][AM] = {0, 0, 0, 0};
    for (int i = 0; i < AN; i++)
    {
        for (int j = 0; j < AM; j++)
        {
            for (int k = 0; k < AM; k++)
            {
            res[i][j] += HP[i][k] * Mult[k][j];
            }
        }
    }
    for (int i = 0; i < AN; i++)
    {
        for (int j = 0; j < AM; j++)
        {
        HP[i][j] = res[i][j];
        }
    }
}

void multing_2(float HP[AM][AM], float Mult[AM][AM])
{
    // HP - HelperMatrix, the matrix we will change
    // It is actually our matrix, cause its massiv
    // so we do not need to use ptr
    // Mult - the matrix we multiply with
    // BTW we save new matrix in the HP
    float res[AM][AM] = {0, 0, 0, 0};
    for (int i = 0; i < AM; i++)
    {
        for (int j = 0; j < AM; j++)
        {
            for (int k = 0; k < AM; k++)
            {
            res[i][j] += HP[i][k] * Mult[k][j];
            }
        }
    }
    for (int i = 0; i < AM; i++)
    {
        for (int j = 0; j < AM; j++)
        {
        HP[i][j] = res[i][j];
        }
    }
}

//----------------------------------------------------------------------------
//============================================================================
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
//=============================Functions of moving============================
//----------------------------------------------------------------------------

void moving(float HPA[AN][AM], float HPB[BN][BM], float dx, float dy, float dz){
    if (AB == 0){
        moving_A(HPA, dx, dy, dz);
    //    find_normals_A(HPA, NORMALS);
    }else{
        moving_B(HPB, dx, dy, dz);
    }
}



void moving_A(float HPA[AN][AM], float dx, float dy, float dz){
    float movingM[AM][AM] = { {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0,1,0},{dx, dy, dz, 1} };
    float HPA_copy[AN][AM];
    for (int i =0; i <AN; i++){
        for(int j=0; j< AM; j++){
            HPA_copy[i][j] = HPA[i][j];
            cout << HPA[i][j] << " ";
        }
        cout <<endl;
    }
    multing_1(HPA_copy, movingM);
    for (int i =0; i <AN; i++){
        if (HPA_copy[i][1] >=0) throw  "under";
    }
    multing_1(HPA, movingM);
    find_center_A(HPA);
}

void moving_B(float HPB[BN][BM], float dx, float dy, float dz){
    float movingM[BM][BM] = { {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0,1,0},{dx, dy, dz, 1} };
    float HPB_copy[BN][BM];
    for (int i =0; i <BN; i++){
        for(int j=0; j< BM; j++){
            HPB_copy[i][j] = HPB[i][j];
            cout << HPB[i][j] << " ";
        }
        cout <<endl;
    }
    multing_2(HPB_copy, movingM);
    for (int i =0; i <BN; i++){
        if (HPB_copy[i][1] >=0) throw  "under";
    }
    multing_2(HPB, movingM);
    find_center_B(HPB);
}

//----------------------------------------------------------------------------
//============================================================================
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
//=========================Functions of rotation==============================
//----------------------------------------------------------------------------

void rotating_A(float HPA[AN][AM], float angle, int index){
    float rotatingM[AM][AM];
    float rotatingM_X[AM][AM] = {
    {1, 0, 0, 0},
    {0, cos(angle), sin(angle), 0},
    {0, -sin(angle), cos(angle), 0},
    {0, 0, 0, 1}    };
    float rotatingM_Y[AM][AM] = {
    {cos(angle), 0, -sin(angle), 0},
    {0, 1, 0, 0},
    {sin(angle), 0, cos(angle), 0},
    {0, 0, 0, 1}    };
    float rotatingM_Z[AM][AM] = {
    {cos(angle), sin(angle), 0, 0},
    {-sin(angle), cos(angle), 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}    };
    for (int i=0; i < AM; i++){
        for (int j=0; j< AM; j++){
            if (index ==1)rotatingM[i][j] = rotatingM_X[i][j];
            if (index ==2)rotatingM[i][j] = rotatingM_Y[i][j];
            if (index ==3)rotatingM[i][j] = rotatingM_Z[i][j];
        }
    }

    float HelperMatrix[AN][AM];

    float HPA_copy[AN][AM];
    for (int i =0; i <AN; i++){
        for(int j=0; j< AM; j++){
            HPA_copy[i][j] = HPA[i][j];
        }
    }

    for (int i = 0; i < AN; i++)
    {
        for (int j = 0; j < AM; j++)
        {
            HelperMatrix[i][j] = HPA_copy[i][j];
        }
    }

    for (int i = 0; i < AN; i++)
    {
        for (int j = 0; j < AM; j++)
        {
            if (j == 0) HelperMatrix[i][j] = HPA_copy[i][j]- AXC;
            if (j == 1) HelperMatrix[i][j] = HPA_copy[i][j]- AYC;
            if (j == 2) HelperMatrix[i][j] = HPA_copy[i][j]- AZC;
        }
    }


    multing_1(HelperMatrix, rotatingM);


    for (int i = 0; i < AN; i++)
    {
        for (int j = 0; j < AM; j++)
        {
            if (j == 0) HPA_copy[i][j] = HelperMatrix[i][j] + AXC;
            if (j == 1) HPA_copy[i][j] = HelperMatrix[i][j] + AYC;
            if (j == 2) HPA_copy[i][j] = HelperMatrix[i][j] + AZC;
        }
    }
    for (int i =0; i <AN; i++){
        if (HPA_copy[i][1] >=0) throw  "under";
    }

    for (int i = 0; i < AN; i++)
    {
        for (int j = 0; j < AM; j++)
        {
            if (j == 0) HPA[i][j] = HPA_copy[i][j];
            if (j == 1) HPA[i][j] = HPA_copy[i][j];
            if (j == 2) HPA[i][j] = HPA_copy[i][j];
        }
    }

    find_center_A(HPA);
}

//----------------------------------------------------------------------------
//============================================================================
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
//=========================Functions of increase decrease=====================
//----------------------------------------------------------------------------

void increese_decreese_A(float HPA[AN][AM], float K){
    float incM[AM][AM] = { {K, 0, 0,0}, {0, K, 0,0}, {0, 0, K, 0}, {0,0,0,1} };
    float HelperMatrix[AN][AM];


    float HPA_copy[AN][AM];
    for (int i =0; i <AN; i++){
        for(int j=0; j< AM; j++){
            HPA_copy[i][j] = HPA[i][j];
        }
    }


     for (int i = 0; i < AN; i++)
    {
        for (int j = 0; j < AM; j++)
        {
            HelperMatrix[i][j] = HPA_copy[i][j];
        }
    }

     for (int i = 0; i < AN; i++)
    {
        for (int j = 0; j < AM; j++)
        {
            if (j == 0) HelperMatrix[i][j] = HPA_copy[i][j]- AXC;
            if (j == 1) HelperMatrix[i][j] = HPA_copy[i][j]- AYC;
            if (j == 2) HelperMatrix[i][j] = HPA_copy[i][j]- AZC;
        }
    }
    multing_1(HelperMatrix, incM);
    for (int i = 0; i < AN; i++)
    {
        for (int j = 0; j < AM; j++)
        {
            if (j == 0) HPA_copy[i][j] = HelperMatrix[i][j] + AXC;
            if (j == 1) HPA_copy[i][j] = HelperMatrix[i][j] + AYC;
            if (j == 2) HPA_copy[i][j] = HelperMatrix[i][j] + AZC;
        }
    }

    for (int i =0; i <AN; i++){
        if (HPA_copy[i][1] >=0) throw  "under";
    }

    for (int i = 0; i < AN; i++)
    {
        for (int j = 0; j < AM; j++)
        {
            if (j == 0) HPA[i][j] = HPA_copy[i][j];
            if (j == 1) HPA[i][j] = HPA_copy[i][j];
            if (j == 2) HPA[i][j] = HPA_copy[i][j];
        }
    }

    find_center_A(HPA);
}

//----------------------------------------------------------------------------
//============================================================================
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
//========================Helping functions==================================
//----------------------------------------------------------------------------

void find_center_A(float HPA[AN][AM]){
    AXC = ((HPA[1][0] + HPA[2][0] + HPA[3][0] + HPA[4][0] )/4 + HPA[0][0])/2;
    AYC = ((HPA[1][1] + HPA[2][1] + HPA[3][1] + HPA[4][1] )/4 + HPA[0][1])/2;
    AZC = ((HPA[1][3] + HPA[2][3] + HPA[3][3] + HPA[4][3] )/4 + HPA[0][3])/2;
}

void find_center_B(float HPB[BN][BM]){
    AXC = ((HPB[1][0] + HPB[2][0] + HPB[3][0])/3 + HPB[0][0])/2;
    AYC = ((HPB[1][1] + HPB[2][1] + HPB[3][1])/3 + HPB[0][1])/2;
    AZC = ((HPB[1][3] + HPB[2][3] + HPB[3][3])/3 + HPB[0][3])/2;
}

/*
void find_normals_A(float HP[AN][AM],float NRM[4][5]){
    int x1, y1, z1;
    int x2, y2, z2;
    int x3, y3, z3;
    int a,b,c,d;

    /* --1-- */
    /*
    x1 = HP[1][0];  x2 = HP[2][0];  x3 = HP[0][0];
    y1 = HP[1][1];  y2 = HP[2][1];  y3 = HP[0][1];
    z1 = HP[1][2];  z2 = HP[2][2];  z3 = HP[0][2];

    a=y1*(z2 - z3) + y2*(z3 - z1) + y3*(z1 - z2);
    b=z1*(x2 - x3) + z2*(x3 - x1) + z3*(x1 - x2);
    c=x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2);
    d=x1*(y2*z3 - y3*z2) + x2*(y3*z1 - y1*z3) + x3*(y1*z2 - y2*z1);

    NRM[0][1] = a;  NRM[1][1] = b; NRM[2][1] = c; NRM[3][1] = d;

    /* --2-- */
    /*
    x1 = HP[3][0];  x2 = HP[2][0];  x3 = HP[0][0];
    y1 = HP[3][1];  y2 = HP[2][1];  y3 = HP[0][1];
    z1 = HP[3][2];  z2 = HP[2][2];  z3 = HP[0][2];

    a=y1*(z2 - z3) + y2*(z3 - z1) + y3*(z1 - z2);
    b=z1*(x2 - x3) + z2*(x3 - x1) + z3*(x1 - x2);
    c=x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2);
    d=x1*(y2*z3 - y3*z2) + x2*(y3*z1 - y1*z3) + x3*(y1*z2 - y2*z1);

    NRM[0][2] = a;  NRM[1][2] = b; NRM[2][2] = c; NRM[3][2] = d;

    /* --3-- */
    /*
    x1 = HP[3][0];  x2 = HP[4][0];  x3 = HP[0][0];
    y1 = HP[3][1];  y2 = HP[4][1];  y3 = HP[0][1];
    z1 = HP[3][2];  z2 = HP[4][2];  z3 = HP[0][2];
/*
    a=y1*(z2 - z3) + y2*(z3 - z1) + y3*(z1 - z2);
    b=z1*(x2 - x3) + z2*(x3 - x1) + z3*(x1 - x2);
    c=x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2);
    d=x1*(y2*z3 - y3*z2) + x2*(y3*z1 - y1*z3) + x3*(y1*z2 - y2*z1);

    NRM[0][3] = a;  NRM[1][3] = b; NRM[2][3] = c; NRM[3][3] = d;

    /* --4-- */
    /*
    x1 = HP[1][0];  x2 = HP[4][0];  x3 = HP[0][0];
    y1 = HP[1][1];  y2 = HP[4][1];  y3 = HP[0][1];
    z1 = HP[1][2];  z2 = HP[4][2];  z3 = HP[0][2];

    a=y1*(z2 - z3) + y2*(z3 - z1) + y3*(z1 - z2);
    b=z1*(x2 - x3) + z2*(x3 - x1) + z3*(x1 - x2);
    c=x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2);
    d=x1*(y2*z3 - y3*z2) + x2*(y3*z1 - y1*z3) + x3*(y1*z2 - y2*z1);

    NRM[0][4] = a;  NRM[1][4] = b; NRM[2][4] = c; NRM[3][4] = d;

    /* --0-- */
    /*
    x1 = HP[3][0];  x2 = HP[2][0];  x3 = HP[1][0];
    y1 = HP[3][1];  y2 = HP[2][1];  y3 = HP[1][1];
    z1 = HP[3][2];  z2 = HP[2][2];  z3 = HP[1][2];

    a=y1*(z2 - z3) + y2*(z3 - z1) + y3*(z1 - z2);
    b=z1*(x2 - x3) + z2*(x3 - x1) + z3*(x1 - x2);
    c=x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2);
    d=x1*(y2*z3 - y3*z2) + x2*(y3*z1 - y1*z3) + x3*(y1*z2 - y2*z1);

    NRM[0][0] = a;  NRM[1][0] = b; NRM[2][0] = c; NRM[3][0] = d;



    for (int i=0; i <4; i++){
        for (int j=0; j <5; j++){
            NRM[i][j] = NRM[i][j]/NRM[3][j];
        }
    } cout << endl;
    for (int i =0; i < 4; i++){
        for(int j=0; j <5; j++){
            cout << NRM[i][j] << " ";
        }
        cout << endl;
    }

    int a,b,c,d;
    a=y1*(z2 - z3) + y2*(z3 - z1) + y3*(z1 - z2);
    b=z1*(x2 - x3) + z2*(x3 - x1) + z3*(x1 - x2);
    c=x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2);
    d=x1*(y2*z3 - y3*z2) + x2*(y3*z1 - y1*z3) + x3*(y1*z2 - y2*z1);
    writeln('Кооффициенты уравнения равны:A=',a,' B=',b,' C=',c,' -D=',d );

}
*/
