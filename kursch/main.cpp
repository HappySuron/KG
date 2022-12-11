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
#define EPS 0.001
#define SHIFT 300


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


#define BX0 80.0
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

#define SELFSHADOW 0
#define BORDERLINE 0


#define N 9
#define M 4

const int AN =5;       // N - amount of conors
const int AM =4;        // M - x,y,z,1

const int BN = 4;
const int BM = 4;

float AXC, AYC, AZC;    // kvazi-Center
float BXC, BYC, BZC;
float ABXC, ABYC, ABZC;


using namespace std;


float PROJECTION[AM][AM] =
    {{0.7, -0.4, 0, 0},
    {0, 0.8, 0, 0},
    {-0.7, -0.4, 1, 0},
    {0, 0, 0, 1}};

    float PROJECTION2[AM][AM] =
    {{1.42, 0.714, 0, 0},
    {0, 1.25, 0, 0},
    {1, 1, 1, 0},
    {0, 0, 0, 1}};         // The matrix of the projection In this case izometria, at least seems to be

/*
float PROJECTION[AM][AM] =
    {{1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 1}};
*/

    int AB=0; // this is the flag to see what figure we are working with right now

//----------------functions----------------------

void Draw_Figure_Both(float HPA[AN][AM], float HPB[BN][BM]);
void Draw_FigureA(float HP[AN][AM]);
void Draw_FigureB(float HP[BN][BM]);


void Draw_Polly(); // to draw the floor, where shadow should be



void multing_1(float HP[AN][AM], float Mult[AM][AM]);
void multing_2(float HP[AM][AM], float Mult[AM][AM]); // Not sure that AM is correct to be used here maybe to change
void multing_3(float HP[3], float Mult[3][3]);
void multing_4(float LG[1][4], float NRM[4][9], float RES[1][9]);
void multing_5 (float FIRST_MT[4][4], float NRM[4][9], float NRM_NEW[4][9]);
void multing_6(float F[1][4], float SND[4][5], float RES[1][4]);
void multing_7(float F[1][4], float SND[4][4], float RES[1][4]);

void find_center_A(float HPA[AN][AM]);
void find_center_B(float HPB[BN][BM]);
void find_center_both();
void find_center_both(float HPA[AN][AM], float HPB[BN][BM]);

void moving_A(float HPA[AN][AM], float dx, float dy, float dz);
void moving_B(float HPB[BN][BM], float dx, float dy, float dz);
void moving(float HPA[AN][AM], float HPB[BN][BM], float dx, float dy, float dz);                       // Here should be two arguments (float HPA[][], HPB[][])
void moving_Both_func(float HPA[AN][AM], float HPB[BN][BM], float dx, float dy, float dz);
                                                                                    // Here should be moving_B
                                                                                    // HTC


void rotating_Both(float HPA[AN][AM], float HPB[BN][BM], float angle, int index);
void rotating_A(float HPA[AN][AM], float angle, int index);
void rotating_B(float HPB[BN][BM], float angle, int index);
void rotating_Both_func(float HPA[AN][AM], float HPB[BN][BM], float angle, int index);
// Here index for
// 1 - x
// 2 - y
// 3 - z
//-----------------------------------------------


void increese_decreese_Both(float HPA[AN][AM], float HPB[BN][BM], float K);
void increese_decreese_A(float HPA[AN][AM], float K);
void increese_decreese_B(float HPB[AN][AM], float K);
void increese_decreese_Both_func(float HPA[AN][AM], float HPB[AN][AM], float K);

//void find_normals_A(float HP[AN][AM], float NRM[4][5]);
void system_solution(float Koordi[3][3], float MFR[3]);
void find_normals(float HPA[AN][AM], float HPB[BN][BM], float NRM[4][9]);




//
void DRAW_figureA_0(float HP[AN][AM], int COl);
void DRAW_figureA_1(float HP[AN][AM], int COl);
void DRAW_figureA_2(float HP[AN][AM], int COl);
void DRAW_figureA_3(float HP[AN][AM], int COl);
void DRAW_figureA_4(float HP[AN][AM], int COl);

void DRAW_figureB_0(float HP[BN][BM], int COl);
void DRAW_figureB_1(float HP[BN][BM], int COl);
void DRAW_figureB_2(float HP[BN][BM], int COl);
void DRAW_figureB_3(float HP[BN][BM], int COl);


void Painting_the_figures(float HPA[AN][AM], float HPB[BN][BM], float CAMxNRM_HP[1][9], float LGHxNRM_HP[1][9]);
void Painting_the_figures_2(float HPA[AN][AM], float HPB[BN][BM], float CAMxNRM_HP[1][9], float LGHxNRM_HP[1][9]);


float NORMALS[4][9];
float NEW_NORMALS[4][9];
float LIGHT[1][4] = {{-100, 5000, -100, 1}};
//float CAMERA[1][4] = {{448, -360, -320, 1}};
float CAMERA[1][4] = {{-1000, -1000, -1000, 1}};

float LIGHTxNORMALS[1][9];
float CAMERAxNORMALS[1][9];
/*
float delta(float matr[3][3])
{
    return matr[0][0]*matr[1][1]*matr[2][2]+matr[0][1]*matr[1][2]*matr[2][0]+matr[1][0]*matr[2][1]*matr[0][2]
            -matr[0][2]*matr[1][1]*matr[2][0]-matr[1][0]*matr[0][1]*matr[2][2]-matr[0][0]*matr[1][2]*matr[2][1];
}

void gen_shadow(float fig [N][M])
{
    // WE SHOULD DEAD PEOPLE
    //30y-8z+240000 = 0;
    //24y - z  = -24000
    float shadow[N][M]; // тут содержаться координаты точок тени
    float del; // ета перемнная содержит определитель
    float st[3][1];
    float res_1[3][1];
    float A[3][3];

    float yt = 100;//-930;
    float xt = 0;//550;
    float zt = 0;//480;

    for (int i = 0; i < N; i++)
    {
        // st[0][0] = xt*(fig[i][1]-yt)-yt*(fig[i][0]-xt);
        // st[1][0] = xt*(fig[i][2]-zt)-zt*(fig[i][0]-xt);
        // st[2][0] = 3600 ;//36000
        st[0][0] = xt*(yt - fig[i][1])-yt*(xt -fig[i][0]);
        st[1][0] = yt*(zt - fig[i][2])-zt*(yt - fig[i][1]);
        st[2][0] = 0 ;//36000

        // A[0][0] = fig[i][1]-yt;
        // A[0][1] = xt-fig[i][0];
        // A[0][2] = 0;

        // A[1][0] = fig[i][2] - zt;
        // A[1][1] = 0;
        // A[1][2] = fig[i][0]-xt;
        A[0][0] = yt-fig[i][1];
        A[0][1] = -(xt-fig[i][0]);
        A[0][2] = 0;

        A[1][1] = zt - fig[i][2];
        A[1][0] = 0;
        A[1][2] = fig[i][1]-yt;

        A[2][0] = 30;
        A[2][1] = 10;
        A[2][2] =27;

        del = delta(A);
        if (del == 0)
        {
            cout << "delta == 0"<<endl;
            return;
        }

        A[0][0] = st[0][0];
        A[1][0] = st[1][0];
        A[2][0] = st[2][0];
        shadow[i][0] = delta(A)/del;
        // A[0][0] = fig[i][1]-yt;
        // A[0][1] = xt-fig[i][0];
        // A[0][2] = 0;

        A[0][0] = yt-fig[i][1];
        A[0][1] = -(xt-fig[i][0]);
        A[0][2] = 0;

        A[0][1] = st[0][0];
        A[1][1] = st[1][0];
        A[2][1] = st[2][0];

        shadow[i][1] = delta(A)/del;

        // A[1][0] = fig[i][2] - zt;
        // A[1][1] = 0;
        // A[1][2] = fig[i][0]-xt;

        A[1][1] = zt - fig[i][2];
        A[1][0] = 0;
        A[1][2] = fig[i][1]-yt;

        A[0][2] = st[0][0];
        A[1][2] = st[1][0];
        A[2][2] = st[2][0];
        shadow[i][2] = delta(A)/del;
        //char* n;
        //*n = i;


    }
    line(xt,yt, shadow[0][0], shadow[0][1]);
    cout << "_________________________" <<endl;
    cout << fig[0][0] << " " << fig[0][1] << " "<< fig[0][2] << endl;
    cout << shadow[0][0] << " " << shadow[0][1] << endl;

    setcolor(WHITE);
    char c;
    char * ptr;
    for (int i = 0; i < 9; i++)
    {
        c = i + 1 +'0';
        ptr = &c;
        outtextxy(shadow[i][0], shadow[i][1], ptr);
    }
    // outtextxy(shadow[9][0], shadow[9][1], "10");
    // outtextxy(shadow[10][0], shadow[10][1], "11");
    // outtextxy(shadow[11][0], shadow[11][1], "12");
    // outtextxy(shadow[12][0], shadow[12][1], "13");
    // outtextxy(shadow[13][0], shadow[13][1], "14");
}

*/

int const Nxx = 3;

float SHADOW[9][4];
float SHADOW_T[4][9];
float SHADOW_FCK[4][9];

double det(float A[Nxx][Nxx])
{
    return A[0][0] * A[1][1] * A[2][2] +
        A[0][1] * A[1][2] * A[2][0] +
        A[1][0] * A[2][1] * A[0][2] -
        A[2][0] * A[1][1] * A[0][2] -
        A[1][0] * A[0][1] * A[2][2] -
        A[2][1] * A[1][2] * A[0][0];
}

void gen_shadow(float HPA[AN][AM], float HPB[BN][BM]) {



    float HLP_MAT[3][3];
    float HLP_MAT_2[3][1];

    for (int step = 0; step < 5; step++) {
        HLP_MAT[0][0] = (HPA[step][1] - LIGHT[0][1]);
        HLP_MAT[0][1] = -(HPA[step][0] - LIGHT[0][0]);
        HLP_MAT[0][2] = 0;

        HLP_MAT[1][0] = 0;
        HLP_MAT[1][1] = (HPA[step][2] - LIGHT[0][2]);
        HLP_MAT[1][2] = -(HPA[step][1] - LIGHT[0][1]);

        HLP_MAT[2][0] = 0.02;
        HLP_MAT[2][1] = -0.007;
        HLP_MAT[2][2] = 0.005;

        HLP_MAT_2[0][0] = (HPA[step][1] - LIGHT[0][1]) * HPA[step][0] - (HPA[step][0] - LIGHT[0][0]) * HPA[step][1];
        HLP_MAT_2[1][0] = (HPA[step][2] - LIGHT[0][2]) * HPA[step][1] - (HPA[step][1] - LIGHT[0][1]) * HPA[step][2];
        HLP_MAT_2[2][0] = -1;
        double X[Nxx];
        float T[Nxx][Nxx];

        double detA;
        int n;
        int i, j;

        detA = det(HLP_MAT);

        for (n = 0; n < Nxx; n++)
        {
            for (i = 0; i < Nxx; i++)
                for (j = 0; j < Nxx; j++)
                    T[i][j] = HLP_MAT[i][j];

            for (j = 0; j < Nxx; j++)
                T[j][n] = HLP_MAT_2[0][j];

            X[n] = det(T) / detA;
        }

        for (i = 0; i < Nxx; i++) {
            SHADOW[step][i] = X[i];
            if (step == 2) {
                cout << "THE STEP 2 " << X[i];
            }
            cout << X[i] << " ";
        }
        cout << "xvcvcvcvcvcvcvcvcv";

        //std::cout << std::endl;
        //std::cout << std::endl;
    }

    for (int step = 0; step < 4; step++) {
        HLP_MAT[0][0] = (HPB[step][1] - LIGHT[0][1]);
        HLP_MAT[0][1] = -(HPB[step][0] - LIGHT[0][0]);
        HLP_MAT[0][2] = 0;

        HLP_MAT[1][0] = 0;
        HLP_MAT[1][1] = (HPB[step][2] - LIGHT[0][2]);
        HLP_MAT[1][2] = -(HPB[step][1] - LIGHT[0][1]);

        HLP_MAT[2][0] = 0.02;
        HLP_MAT[2][1] = -0.007;
        HLP_MAT[2][2] = 0.005;

        HLP_MAT_2[0][0] = (HPB[step][1] - LIGHT[0][1]) * HPB[step][0] - (HPB[step][0] - LIGHT[0][0]) * HPB[step][1];
        HLP_MAT_2[1][0] = (HPB[step][2] - LIGHT[0][2]) * HPB[step][1] - (HPB[step][1] - LIGHT[0][1]) * HPB[step][2];
        HLP_MAT_2[2][0] = -1;
        double X[Nxx];
        float T[Nxx][Nxx];

        double detA;
        int n;
        int i, j;

        detA = det(HLP_MAT);

        for (n = 0; n < Nxx; n++)
        {
            for (i = 0; i < Nxx; i++)
                for (j = 0; j < Nxx; j++)
                    T[i][j] = HLP_MAT[i][j];

            for (j = 0; j < Nxx; j++)
                T[j][n] = HLP_MAT_2[0][j];

            X[n] = det(T) / detA;
        }

        for (i = 0; i < Nxx; i++)
            SHADOW[step + 5][i] = X[i];


        //std::cout << std::endl;
        //std::cout << std::endl;
    }


    /*
    for (int i =0; i <9; i++){
           for (int j =0; j < 4; j++)
           {
                SHADOW_T[j][i] = SHADOW[i][j];
            }
        }
    for (int i =0; i <9; i++)
        SHADOW_T[3][i] =1;
    multing_5(PROJECTION, SHADOW_T, SHADOW_FCK);
    */
}


int main(){
    system("gcc -v");
    cout.precision(2);
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");

    setcolor(BLACK);                    // Just some pre-things
    setfillstyle(SOLID_FILL,WHITE);     // To make sure its white
    bar(0,0,640,480);                   //


    float AFG[AN][AM] = {{AX0,AY0,AZ0, 1}, {AX1,AY1,AZ1, 1}, {AX2,AY2,AZ2, 1},{AX3,AY3,AZ3, 1},{AX4,AY4,AZ4, 1}};
    float BFG[BN][BM] = {{BX0, BY0, BZ0, 1}, {BX1, BY1, BZ1, 1}, {BX2, BY2, BZ2, 1}, {BX3, BY3, BZ3, 1}};

      //std::cout << AFG[3][2] << " ";

    gen_shadow(AFG, BFG);
    cout << "-----------------------SH-----------------" <<endl;
    for (int i =0; i <9; i++){
        for (int j =0; j < 4; j++)
        {
        cout << SHADOW[i][j] << " ";
        }
        cout << endl;
    }

    cout  << "------------------------------------------" << endl;













    // Filling D koof with
    for (int i =0; i < 9; i++){
        NORMALS[3][i] = 1;
    }





    /* to check the koords
    cout << AX1 << " " << AY1 << " " << AZ1 << endl;
    cout << AX2 << " " << AY2 << " " << AZ2 << endl;
    cout << AX3 << " " << AY3 << " " << AZ3 << endl;
    cout << AX4 << " " << AY4 << " " << AZ4 << endl;
    cout << AX0 << " " << AY0 << " " << AZ0 << endl;
    */





    //line(SHADOW[0][0]+SHIFT, SHADOW[1][0]+SHIFT, SHADOW[0][1]+SHIFT, SHADOW[1][1]+SHIFT);



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
            case 'o':  {rotating_Both(AFG, BFG, UG, 1);
                        break;}
            case 'u':  {rotating_Both(AFG, BFG, -UG, 1);
                        break;}
            case 'i':  {rotating_Both(AFG, BFG, UG, 2);
                        break;}
            case 'k':  {rotating_Both(AFG, BFG, -UG, 2);
                        break;}
            case 'j':  {rotating_Both(AFG, BFG, UG, 3);
                        break;}
            case 'l':  {rotating_Both(AFG, BFG, -UG, 3);
                        break;}
            case 'z':  {increese_decreese_Both(AFG, BFG, INC);
                        break;}
            case 'c':  {increese_decreese_Both(AFG, BFG, DEC);
                        break;}
            case '1': { AB=0;
                        break;}
            case '2': { AB=1;
                        break;}
            case '3': { AB=2;
                        break;}
        }

        //////////////////////////////////////////////////////////
        setcolor(BLACK);
        setfillstyle(SOLID_FILL,WHITE);
        bar(0,0,640,480);
        Draw_Figure_Both(AFG, BFG);
        }catch (char const* err){
        // cout << err;
        }
        find_center_A(AFG);
        find_center_B(BFG);
        find_normals(AFG, BFG, NORMALS);










        /*
        for (int i =0; i <4; i++){
             for (int j=0; j < 9; j++){
                cout  << NORMALS[i][j]<<'\t';
            }
            cout << endl;
        }*/








        multing_4(LIGHT, NORMALS, LIGHTxNORMALS);








/*
        cout << endl;
        cout << endl;
        for (int i =0; i <9; i++){
            cout  << LIGHTxNORMALS[0][i] << " ";
        }cout << endl;




        cout <<endl << "************************AG" << endl;
        for (int i =0; i <5; i++){
        for (int j=0; j <4; j++){
            cout << AFG[i][j] << '\t';
        }
        cout <<endl;
        }

         cout <<endl << "************************NRM" << endl;
        for (int i =0; i <4; i++){
        for (int j=0; j <9; j++){
            cout << NORMALS[i][j] << '\t';
        }
        cout <<endl;
        }


        //multing_5(PROJECTION2, NORMALS, NEW_NORMALS);

        cout <<endl << "************************NNMRM" << endl;
        for (int i =0; i <4; i++){
        for (int j=0; j <9; j++){
            cout << NEW_NORMALS[i][j] << '\t';
        }
        cout <<endl;
        }
*/




        multing_4(CAMERA, NORMALS, CAMERAxNORMALS);




        //cout << endl;
       // cout << endl;
       /*
        for (int i =0; i <9; i++){
                cout << "CAMERAxNORMALS" << endl;
            cout  << CAMERAxNORMALS[0][i] << " ";
        }cout << endl;
        */










        cout << "sdassafdasdf" << (AXC + AYC + AZC) << " " <<(BXC + BYC + BZC) << endl;
        if ((AXC + AYC + AZC) < (BXC + BYC + BZC)){
        Painting_the_figures(AFG, BFG, CAMERAxNORMALS, LIGHTxNORMALS);
        Painting_the_figures_2(AFG, BFG, CAMERAxNORMALS, LIGHTxNORMALS);
        }else {
        Painting_the_figures_2(AFG, BFG, CAMERAxNORMALS, LIGHTxNORMALS);
        Painting_the_figures(AFG, BFG, CAMERAxNORMALS, LIGHTxNORMALS);
        }





        if(BORDERLINE == 1){
        Draw_FigureA(AFG);
        Draw_FigureB(BFG);}
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

    float fig [N][M];                                                                            //DELETE THIS PIECE OF SHIT
    for (int i=0; i< AN; i++){
        for(int j =0; j < AM; j++){
            fig [i][j] = HPA[i][j];
        }
    }
    for (int i=0; i< BN; i++){
        for(int j =0; j < BM; j++){
            fig [i+AM][j] = HPB[i][j];
        }
    }

    //gen_shadow(fig);
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
        line (round(TDO[i][0])+SHIFT, round(TDO[i][1])+SHIFT, round(TDO[i+1][0])+SHIFT, round(TDO[i+1][1])+SHIFT);
    }
    line (round(TDO[1][0])+SHIFT, round(TDO[1][1])+SHIFT, round(TDO[AN-1][0])+SHIFT, round(TDO[AN-1][1])+SHIFT);

    for (int i=1; i < AN; i++){
        line (round(TDO[i][0])+SHIFT, round(TDO[i][1])+SHIFT, round(TDO[0][0])+SHIFT, round(TDO[0][1])+SHIFT);
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
        line (round(TDO[i][0])+SHIFT, round(TDO[i][1])+SHIFT, round(TDO[i+1][0])+SHIFT, round(TDO[i+1][1])+SHIFT);
    }
    line (round(TDO[1][0])+SHIFT, round(TDO[1][1])+SHIFT, round(TDO[BN-1][0])+SHIFT, round(TDO[BN-1][1])+SHIFT);

    for (int i=1; i < BN; i++){
        line (round(TDO[i][0])+SHIFT, round(TDO[i][1])+SHIFT, round(TDO[0][0])+SHIFT, round(TDO[0][1])+SHIFT);
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
    poly[0] = Polly[0][0]+SHIFT;              // | the square
    poly[1] = Polly[0][1]+SHIFT;              // | before fillpoly make it
                                            // V look good
    poly[2] = Polly[1][0]+SHIFT;
    poly[3] = Polly[1][1]+SHIFT;

    poly[4] = Polly[2][0]+SHIFT;
    poly[5] = Polly[2][1]+SHIFT;

    poly[6] = Polly[3][0]+SHIFT;
    poly[7] = Polly[3][1]+SHIFT;

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

void multing_3(float HP[3], float Mult[3][3])    // Is used in system_solution
{
    for (int i =0; i <3; i++) HP[i] = -1;                   // To find A B C
    float res[3] = { 0, 0, 0 };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            res[i] += HP[i] * Mult[i][j];
        }
    }
    for (int i = 0; i < 3; i++)
    {
        HP[i] = res[i];
    }
}

void multing_4 (float LG[1][4], float NRM[4][9], float RES[1][9]){
    for (int i = 0; i < 9; i++) {
            RES[0][i] =0;
        }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 9; j++) {
            RES[0][j] += LG[0][i] * NRM[i][j];
        }
    }
}

void multing_5 (float FIRST_MT[4][4], float NRM[4][9], float NRM_NEW[4][9]){
    for (int i =0; i <4; i++)
        for (int j =0; j <9; j++)
            NRM_NEW[i][j] =0;


    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            for (int k = 0; k < 4; k++)
            {
            NRM_NEW[i][j] += FIRST_MT[i][k] * NRM[k][j];
            }
        }
    }
}

void multing_6(float F[1][4], float SND[4][5], float RES[1][5]){
    for (int i = 0; i < 9; i++) {
            RES[0][i] =0;
        }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            RES[0][j] += F[0][i] * SND[i][j];
        }
    }
}

void multing_7(float F[1][4], float SND[4][4], float RES[1][4]){
    for (int i = 0; i < 4; i++) {
            RES[0][i] =0;
        }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            RES[0][j] += F[0][i] * SND[i][j];
            //cout << RES[0][j] << " ";
        }
    }

    for (int j = 0; j < 4; j++) {
            cout << RES[0][j] << " ";
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
    } else if (AB == 1){
        moving_B(HPB, dx, dy, dz);
    }
    else{
        moving_Both_func(HPA, HPB, dx, dy, dz);
    }
    find_center_A(HPA);
    find_center_B(HPB);
}



void moving_A(float HPA[AN][AM], float dx, float dy, float dz){
    float movingM[AM][AM] = { {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0,1,0},{dx, dy, dz, 1} };
    float HPA_copy[AN][AM];
    for (int i =0; i <AN; i++){
        for(int j=0; j< AM; j++){
            HPA_copy[i][j] = HPA[i][j];
    //        cout << HPA[i][j] << " ";
        }
    //    cout <<endl;
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
    //        cout << HPB[i][j] << " ";
        }
    //    cout <<endl;
    }
    multing_2(HPB_copy, movingM);
    for (int i =0; i <BN; i++){
        if (HPB_copy[i][1] >=0) throw  "under";
    }
    multing_2(HPB, movingM);
    find_center_B(HPB);
}

void moving_Both_func(float HPA[AN][AM], float HPB[BN][BM], float dx, float dy, float dz){
    float movingMA[AM][AM] = { {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0,1,0},{dx, dy, dz, 1} };
    float HPA_copy[AN][AM];
    for (int i =0; i <AN; i++){
        for(int j=0; j< AM; j++){
            HPA_copy[i][j] = HPA[i][j];
    //        cout << HPA[i][j] << " ";
        }
    //    cout <<endl;
    }
    multing_1(HPA_copy, movingMA);
    for (int i =0; i <AN; i++){
        if (HPA_copy[i][1] >=0) throw  "under";
    }



    float movingMB[BM][BM] = { {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0,1,0},{dx, dy, dz, 1} };
    float HPB_copy[BN][BM];
    for (int i =0; i <BN; i++){
        for(int j=0; j< BM; j++){
            HPB_copy[i][j] = HPB[i][j];
    //        cout << HPB[i][j] << " ";
        }
    //    cout <<endl;
    }
    multing_2(HPB_copy, movingMB);

    for (int i =0; i <BN; i++){
        if (HPB_copy[i][1] >=0) throw  "under";
    }

    multing_1(HPA, movingMA);
    multing_2(HPB, movingMB);
    find_center_A(HPA);
    find_center_B(HPB);
    find_center_both();
}

//----------------------------------------------------------------------------
//============================================================================
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
//=========================Functions of rotation==============================
//----------------------------------------------------------------------------

void rotating_Both(float HPA[AN][AM], float HPB[BN][BM], float angle, int index){
    if (AB == 0){
        rotating_A(HPA, angle, index);
    //    find_normals_A(HPA, NORMALS);
    }else if (AB == 1){
         rotating_B(HPB, angle, index);
    }
    else {
        rotating_Both_func(HPA, HPB,  angle, index);
    }
}



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



    if (AB == 2){
        AXC = ABXC;
        AYC = ABYC;
        AZC = ABZC;
    }


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
    find_center_both();
}

void rotating_B(float HPB[BN][BM], float angle, int index){
    float rotatingM[BM][BM];
    float rotatingM_X[BM][BM] = {
    {1, 0, 0, 0},
    {0, cos(angle), sin(angle), 0},
    {0, -sin(angle), cos(angle), 0},
    {0, 0, 0, 1}    };
    float rotatingM_Y[BM][BM] = {
    {cos(angle), 0, -sin(angle), 0},
    {0, 1, 0, 0},
    {sin(angle), 0, cos(angle), 0},
    {0, 0, 0, 1}    };
    float rotatingM_Z[BM][BM] = {
    {cos(angle), sin(angle), 0, 0},
    {-sin(angle), cos(angle), 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}    };



    if (AB == 2){
        BXC = ABXC;
        BYC = ABYC;
        BZC = ABZC;
    }


    for (int i=0; i < BM; i++){
        for (int j=0; j< BM; j++){
            if (index ==1)rotatingM[i][j] = rotatingM_X[i][j];
            if (index ==2)rotatingM[i][j] = rotatingM_Y[i][j];
            if (index ==3)rotatingM[i][j] = rotatingM_Z[i][j];
        }
    }

    float HelperMatrix[BN][BM];

    float HPB_copy[BN][BM];
    for (int i =0; i <BN; i++){
        for(int j=0; j< BM; j++){
            HPB_copy[i][j] = HPB[i][j];
        }
    }

    for (int i = 0; i < BN; i++)
    {
        for (int j = 0; j < BM; j++)
        {
            HelperMatrix[i][j] = HPB_copy[i][j];
        }
    }

    for (int i = 0; i < BN; i++)
    {
        for (int j = 0; j < BM; j++)
        {
            if (j == 0) HelperMatrix[i][j] = HPB_copy[i][j]- BXC;
            if (j == 1) HelperMatrix[i][j] = HPB_copy[i][j]- BYC;
            if (j == 2) HelperMatrix[i][j] = HPB_copy[i][j]- BZC;
        }
    }


    multing_2(HelperMatrix, rotatingM);


    for (int i = 0; i < BN; i++)
    {
        for (int j = 0; j < BM; j++)
        {
            if (j == 0) HPB_copy[i][j] = HelperMatrix[i][j] + BXC;
            if (j == 1) HPB_copy[i][j] = HelperMatrix[i][j] + BYC;
            if (j == 2) HPB_copy[i][j] = HelperMatrix[i][j] + BZC;
        }
    }
    for (int i =0; i <BN; i++){
        if (HPB_copy[i][1] >=0) throw  "under";
    }

    for (int i = 0; i < BN; i++)
    {
        for (int j = 0; j < BM; j++)
        {
            if (j == 0) HPB[i][j] = HPB_copy[i][j];
            if (j == 1) HPB[i][j] = HPB_copy[i][j];
            if (j == 2) HPB[i][j] = HPB_copy[i][j];
        }
    }

    find_center_B(HPB);
    find_center_both();
}


void rotating_Both_func(float HPA[AN][AM], float HPB[BN][BM], float angle, int index){
    float rotatingMA[AM][AM];
    float rotatingM_XA[AM][AM] = {
    {1, 0, 0, 0},
    {0, cos(angle), sin(angle), 0},
    {0, -sin(angle), cos(angle), 0},
    {0, 0, 0, 1}    };
    float rotatingM_YA[AM][AM] = {
    {cos(angle), 0, -sin(angle), 0},
    {0, 1, 0, 0},
    {sin(angle), 0, cos(angle), 0},
    {0, 0, 0, 1}    };
    float rotatingM_ZA[AM][AM] = {
    {cos(angle), sin(angle), 0, 0},
    {-sin(angle), cos(angle), 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}    };


    for (int i=0; i < AM; i++){
        for (int j=0; j< AM; j++){
            if (index ==1)rotatingMA[i][j] = rotatingM_XA[i][j];
            if (index ==2)rotatingMA[i][j] = rotatingM_YA[i][j];
            if (index ==3)rotatingMA[i][j] = rotatingM_ZA[i][j];
        }
    }

    float HelperMatrixA[AN][AM];

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
            HelperMatrixA[i][j] = HPA_copy[i][j];
        }
    }

    for (int i = 0; i < AN; i++)
    {
        for (int j = 0; j < AM; j++)
        {
            if (j == 0) HelperMatrixA[i][j] = HPA_copy[i][j]- ABXC;
            if (j == 1) HelperMatrixA[i][j] = HPA_copy[i][j]- ABYC;
            if (j == 2) HelperMatrixA[i][j] = HPA_copy[i][j]- ABZC;
        }
    }


    multing_1(HelperMatrixA, rotatingMA);


    for (int i = 0; i < AN; i++)
    {
        for (int j = 0; j < AM; j++)
        {
            if (j == 0) HPA_copy[i][j] = HelperMatrixA[i][j] + ABXC;
            if (j == 1) HPA_copy[i][j] = HelperMatrixA[i][j] + ABYC;
            if (j == 2) HPA_copy[i][j] = HelperMatrixA[i][j] + ABZC;
        }
    }
    for (int i =0; i <AN; i++){
        if (HPA_copy[i][1] >=0) throw  "under";
    }






    float rotatingMB[BM][BM];
    float rotatingM_XB[BM][BM] = {
    {1, 0, 0, 0},
    {0, cos(angle), sin(angle), 0},
    {0, -sin(angle), cos(angle), 0},
    {0, 0, 0, 1}    };
    float rotatingM_YB[BM][BM] = {
    {cos(angle), 0, -sin(angle), 0},
    {0, 1, 0, 0},
    {sin(angle), 0, cos(angle), 0},
    {0, 0, 0, 1}    };
    float rotatingM_ZB[BM][BM] = {
    {cos(angle), sin(angle), 0, 0},
    {-sin(angle), cos(angle), 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}    };






    for (int i=0; i < BM; i++){
        for (int j=0; j< BM; j++){
            if (index ==1)rotatingMB[i][j] = rotatingM_XB[i][j];
            if (index ==2)rotatingMB[i][j] = rotatingM_YB[i][j];
            if (index ==3)rotatingMB[i][j] = rotatingM_ZB[i][j];
        }
    }

    float HelperMatrixB[BN][BM];

    float HPB_copy[BN][BM];
    for (int i =0; i <BN; i++){
        for(int j=0; j< BM; j++){
            HPB_copy[i][j] = HPB[i][j];
        }
    }

    for (int i = 0; i < BN; i++)
    {
        for (int j = 0; j < BM; j++)
        {
            HelperMatrixB[i][j] = HPB_copy[i][j];
        }
    }

    for (int i = 0; i < BN; i++)
    {
        for (int j = 0; j < BM; j++)
        {
            if (j == 0) HelperMatrixB[i][j] = HPB_copy[i][j]- ABXC;
            if (j == 1) HelperMatrixB[i][j] = HPB_copy[i][j]- ABYC;
            if (j == 2) HelperMatrixB[i][j] = HPB_copy[i][j]- ABZC;
        }
    }


    multing_2(HelperMatrixB, rotatingMB);


    for (int i = 0; i < BN; i++)
    {
        for (int j = 0; j < BM; j++)
        {
            if (j == 0) HPB_copy[i][j] = HelperMatrixB[i][j] + ABXC;
            if (j == 1) HPB_copy[i][j] = HelperMatrixB[i][j] + ABYC;
            if (j == 2) HPB_copy[i][j] = HelperMatrixB[i][j] + ABZC;
        }
    }
    for (int i =0; i <BN; i++){
        if (HPB_copy[i][1] >=0) throw  "under";
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

    for (int i = 0; i < BN; i++)
    {
        for (int j = 0; j < BM; j++)
        {
            if (j == 0) HPB[i][j] = HPB_copy[i][j];
            if (j == 1) HPB[i][j] = HPB_copy[i][j];
            if (j == 2) HPB[i][j] = HPB_copy[i][j];
        }
    }

    find_center_A(HPA);
    find_center_B(HPB);
    find_center_both();

}

//----------------------------------------------------------------------------
//============================================================================
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
//=========================Functions of increase decrease=====================
//----------------------------------------------------------------------------

void increese_decreese_Both(float HPA[AN][AM], float HPB[BN][BM], float K){
    if (AB == 0){
        increese_decreese_A(HPA,K);
    //    find_normals_A(HPA, NORMALS);
    }else if (AB == 1){
         increese_decreese_B(HPB,K);
    } else {
        increese_decreese_Both_func(HPA, HPB, K);
    }
}

void increese_decreese_A(float HPA[AN][AM], float K){


    float incM[AM][AM] = { {K, 0, 0,0}, {0, K, 0,0}, {0, 0, K, 0}, {0,0,0,1} };
    float HelperMatrix[AN][AM];



    if (AB == 2){
        AXC = ABXC;
        AYC = ABYC;
        AZC = ABZC;
    }


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
    find_center_both();
}

void increese_decreese_B(float HPB[AN][AM], float K){
    float incM[BM][BM] = { {K, 0, 0,0}, {0, K, 0,0}, {0, 0, K, 0}, {0,0,0,1} };
    float HelperMatrix[BN][BM];



    if (AB == 2){
        BXC = ABXC;
        BYC = ABYC;
        BZC = ABZC;
    }



    float HPB_copy[BN][BM];
    for (int i =0; i <BN; i++){
        for(int j=0; j< BM; j++){
            HPB_copy[i][j] = HPB[i][j];
        }
    }


     for (int i = 0; i < BN; i++)
    {
        for (int j = 0; j < BM; j++)
        {
            HelperMatrix[i][j] = HPB_copy[i][j];
        }
    }

     for (int i = 0; i < BN; i++)
    {
        for (int j = 0; j < BM; j++)
        {
            if (j == 0) HelperMatrix[i][j] = HPB_copy[i][j]- BXC;
            if (j == 1) HelperMatrix[i][j] = HPB_copy[i][j]- BYC;
            if (j == 2) HelperMatrix[i][j] = HPB_copy[i][j]- BZC;
        }
    }
    multing_2(HelperMatrix, incM);
    for (int i = 0; i < BN; i++)
    {
        for (int j = 0; j < BM; j++)
        {
            if (j == 0) HPB_copy[i][j] = HelperMatrix[i][j] + BXC;
            if (j == 1) HPB_copy[i][j] = HelperMatrix[i][j] + BYC;
            if (j == 2) HPB_copy[i][j] = HelperMatrix[i][j] + BZC;
        }
    }

    for (int i =0; i <BN; i++){
        if (HPB_copy[i][1] >=0) throw  "under";
    }

    for (int i = 0; i < BN; i++)
    {
        for (int j = 0; j < BM; j++)
        {
            if (j == 0) HPB[i][j] = HPB_copy[i][j];
            if (j == 1) HPB[i][j] = HPB_copy[i][j];
            if (j == 2) HPB[i][j] = HPB_copy[i][j];
        }
    }

    find_center_B(HPB);
    find_center_both();
}

void increese_decreese_Both_func(float HPA[AN][AM], float HPB[AN][AM], float K){
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
            if (j == 0) HelperMatrix[i][j] = HPA_copy[i][j]- ABXC;
            if (j == 1) HelperMatrix[i][j] = HPA_copy[i][j]- ABYC;
            if (j == 2) HelperMatrix[i][j] = HPA_copy[i][j]- ABZC;
        }
    }
    multing_1(HelperMatrix, incM);
    for (int i = 0; i < AN; i++)
    {
        for (int j = 0; j < AM; j++)
        {
            if (j == 0) HPA_copy[i][j] = HelperMatrix[i][j] + ABXC;
            if (j == 1) HPA_copy[i][j] = HelperMatrix[i][j] + ABYC;
            if (j == 2) HPA_copy[i][j] = HelperMatrix[i][j] + ABZC;
        }
    }

    for (int i =0; i <AN; i++){
        if (HPA_copy[i][1] >=0) throw  "under";
    }







    float HPB_copy[BN][BM];
    for (int i =0; i <BN; i++){
        for(int j=0; j< BM; j++){
            HPB_copy[i][j] = HPB[i][j];
        }
    }


     for (int i = 0; i < BN; i++)
    {
        for (int j = 0; j < BM; j++)
        {
            HelperMatrix[i][j] = HPB_copy[i][j];
        }
    }

     for (int i = 0; i < BN; i++)
    {
        for (int j = 0; j < BM; j++)
        {
            if (j == 0) HelperMatrix[i][j] = HPB_copy[i][j]- ABXC;
            if (j == 1) HelperMatrix[i][j] = HPB_copy[i][j]- ABYC;
            if (j == 2) HelperMatrix[i][j] = HPB_copy[i][j]- ABZC;
        }
    }
    multing_2(HelperMatrix, incM);
    for (int i = 0; i < BN; i++)
    {
        for (int j = 0; j < BM; j++)
        {
            if (j == 0) HPB_copy[i][j] = HelperMatrix[i][j] + ABXC;
            if (j == 1) HPB_copy[i][j] = HelperMatrix[i][j] + ABYC;
            if (j == 2) HPB_copy[i][j] = HelperMatrix[i][j] + ABZC;
        }
    }

    for (int i =0; i <BN; i++){
        if (HPB_copy[i][1] >=0) throw  "under";
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



    for (int i = 0; i < BN; i++)
    {
        for (int j = 0; j < BM; j++)
        {
            if (j == 0) HPB[i][j] = HPB_copy[i][j];
            if (j == 1) HPB[i][j] = HPB_copy[i][j];
            if (j == 2) HPB[i][j] = HPB_copy[i][j];
        }
    }

    find_center_A(HPA);
    find_center_B(HPB);
    find_center_both();
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
    AZC = ((HPA[1][2] + HPA[2][2] + HPA[3][2] + HPA[4][2] )/4 + HPA[0][2])/2;

    //cout << HPA[1][3] << " " <<  HPA[2][3] << " " << HPA[3][3] << " " <<  HPA[4][3] << " " << HPA[0][3] << endl;
}

void find_center_B(float HPB[BN][BM]){
    BXC = ((HPB[1][0] + HPB[2][0] + HPB[3][0])/3 + HPB[0][0])/2;
    BYC = ((HPB[1][1] + HPB[2][1] + HPB[3][1])/3 + HPB[0][1])/2;
    BZC = ((HPB[1][2] + HPB[2][2] + HPB[3][2])/3 + HPB[0][2])/2;
}

void find_center_both(){
    ABXC = (AXC + BXC)/2;
    ABYC = (AYC + BYC)/2;
    ABZC = (AZC + BZC)/2;
     //

     //
}

void find_center_both(float HPA[AN][AM], float HPB[BN][BM]){
    ABXC = ( ((HPA[1][0] + HPA[2][0] + HPA[3][0] + HPA[4][0] )/4 + HPA[0][0])/2 + ((HPB[1][0] + HPB[2][0] + HPB[3][0])/3 + HPB[0][0])/2 );
    ABYC = ( ((HPA[1][1] + HPA[2][1] + HPA[3][1] + HPA[4][1] )/4 + HPA[0][1])/2 + ((HPB[1][1] + HPB[2][1] + HPB[3][1])/3 + HPB[0][1])/2 );
    ABZC = ( ((HPA[1][2] + HPA[2][2] + HPA[3][2] + HPA[4][2] )/4 + HPA[0][2])/2 + ((HPB[1][2] + HPB[2][2] + HPB[3][2])/3 + HPB[0][2])/2 );

        cout << "Avar A koords: " << AXC << " " << AYC << " " << AZC << endl;
        cout << "Avar B koords: " << BXC << " " << BYC << " " << BZC << endl;
        cout << "Avar Both koords"  << ABXC << " " << ABYC << " " << ABZC << endl;
}



void system_solution(float Koordi[3][3], float MFR[]) {
    // MFR - matrix for result, mb wrong and fix
        // | rewrite koord into x y z                       // Is used to find normals
        // | not to burn out by [][]
        // V
    float x1, y1, z1;
    float x2, y2, z2;
    float x3, y3, z3;
    x1 = Koordi[0][0]; x2 = Koordi[1][0]; x3 = Koordi[2][0];
    y1 = Koordi[0][1]; y2 = Koordi[1][1]; y3 = Koordi[2][1];
    z1 = Koordi[0][2]; z2 = Koordi[1][2]; z3 = Koordi[2][2];

    float delta1 = (x1 * y2 * z3 + x2 * y3 * z1 + x3 * y1 * z2);
    float delta2 = (z1 * y2 * x3 + z2 * y3 * x1 + z3 * y1 * x2);
    float delta = delta1 - delta2;
    cout << "--------------" << delta << endl;

    std::cout <<"delta " << delta << std::endl << std::endl;

    if (delta ==0){
    delta1 = ((x1+ EPS) * y2 * z3 + x2 * y3 * z1 + x3 * y1 * z2);
    delta2 = (z1 * y2 * x3 + z2 * y3 * x1 + z3 * y1 * x2);
    delta = delta1 - delta2;
    }
    std::cout <<"delta new " << delta << std::endl << std::endl;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << Koordi[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // there is no God below... We will count minors in the array
    float C[3][3] = {
    {(y2 * z3 - z2 * y3), (-1) * (y1 * z3 - z1 * y3), (y1 * z2 - z1 * y2)},
    {(-1) * (x2 * z3 - z2 * x3), (x1 * z3 - z1 * x3), (-1) * (x1 * z2 - z1 * x2)},
    {(x2 * y3 - y2 * x3), (-1) * (x1 * y3 - y1 * x3), (x1 * y2 - y1 * x2)},
    };

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << C[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            C[i][j] = C[i][j] / delta;
        }
    }

    /*
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
           std::cout << C[i][j] << " ";
        }
        std::cout << std::endl;
    }
    */
    // mb fix do not HardCode
    for (int i = 0; i < 3; i++) {
        MFR[i] = -1;
    }

    multing_3(MFR, C);
}


void find_normals(float HPA[AN][AM], float HPB[BN][BM], float NRM[4][9]){
    float KoordMatrix[3][3]; // her we will store koords
    float ResultMatrix[3] = {-1, -1, -1}; //result will be stored here

    for (int i=0; i<9; i++) NRM[3][i]=1;
    //---A-0---
    for (int j=0; j< 3; j++) KoordMatrix[0][j] = HPA[1][j]; // --1
    for (int j=0; j< 3; j++) KoordMatrix[1][j] = HPA[2][j]; // --2
    for (int j=0; j< 3; j++) KoordMatrix[2][j] = HPA[3][j]; // --3
    system_solution(KoordMatrix, ResultMatrix);
    for (int i=0; i <3; i++) NRM[i][0] = ResultMatrix[i];



    //--A-1---
    for (int j=0; j< 3; j++) KoordMatrix[0][j] = HPA[0][j]; // --0
    for (int j=0; j< 3; j++) KoordMatrix[1][j] = HPA[1][j]; // --1
    for (int j=0; j< 3; j++) KoordMatrix[2][j] = HPA[2][j]; // --2
    system_solution(KoordMatrix, ResultMatrix);
    for (int i=0; i <3; i++) NRM[i][1] = ResultMatrix[i];

    //---A-2---
    for (int j=0; j< 3; j++) KoordMatrix[0][j] = HPA[0][j]; // --0
    for (int j=0; j< 3; j++) KoordMatrix[1][j] = HPA[2][j]; // --2
    for (int j=0; j< 3; j++) KoordMatrix[2][j] = HPA[3][j]; // --3
    system_solution(KoordMatrix, ResultMatrix);
    for (int i=0; i <3; i++) NRM[i][2] = ResultMatrix[i];

    //---A-3---
    for (int j=0; j< 3; j++) KoordMatrix[0][j] = HPA[0][j]; // --0
    for (int j=0; j< 3; j++) KoordMatrix[1][j] = HPA[3][j]; // --3
    for (int j=0; j< 3; j++) KoordMatrix[2][j] = HPA[4][j]; // --4
    system_solution(KoordMatrix, ResultMatrix);
    for (int i=0; i <3; i++) NRM[i][3] = ResultMatrix[i];

    //---A-4---
    for (int j=0; j< 3; j++) KoordMatrix[0][j] = HPA[0][j]; // --0
    for (int j=0; j< 3; j++) KoordMatrix[1][j] = HPA[1][j]; // --1
    for (int j=0; j< 3; j++) KoordMatrix[2][j] = HPA[4][j]; // --4
    system_solution(KoordMatrix, ResultMatrix);
    for (int i=0; i <3; i++) NRM[i][4] = ResultMatrix[i];




    //---B-0---
    for (int j=0; j< 3; j++) KoordMatrix[0][j] = HPB[1][j]; // --1
    for (int j=0; j< 3; j++) KoordMatrix[1][j] = HPB[2][j]; // --2
    for (int j=0; j< 3; j++) KoordMatrix[2][j] = HPB[3][j]; // --3
    system_solution(KoordMatrix, ResultMatrix);
    for (int i=0; i <3; i++) NRM[i][5] = ResultMatrix[i];
    //---B-1---
    for (int j=0; j< 3; j++) KoordMatrix[0][j] = HPB[0][j]; // --0
    for (int j=0; j< 3; j++) KoordMatrix[1][j] = HPB[1][j]; // --1
    for (int j=0; j< 3; j++) KoordMatrix[2][j] = HPB[2][j]; // --2
    system_solution(KoordMatrix, ResultMatrix);
    for (int i=0; i <3; i++) NRM[i][6] = ResultMatrix[i];
    //---B-2---
    for (int j=0; j< 3; j++) KoordMatrix[0][j] = HPB[0][j]; // --0
    for (int j=0; j< 3; j++) KoordMatrix[1][j] = HPB[2][j]; // --2
    for (int j=0; j< 3; j++) KoordMatrix[2][j] = HPB[3][j]; // --3
    system_solution(KoordMatrix, ResultMatrix);
    for (int i=0; i <3; i++) NRM[i][7] = ResultMatrix[i];
    //---B-3---
    for (int j=0; j< 3; j++) KoordMatrix[0][j] = HPB[0][j]; // --0
    for (int j=0; j< 3; j++) KoordMatrix[1][j] = HPB[1][j]; // --1
    for (int j=0; j< 3; j++) KoordMatrix[2][j] = HPB[3][j]; // --3

    system_solution(KoordMatrix, ResultMatrix);
    for (int i=0; i <3; i++) NRM[i][8] = ResultMatrix[i];

    //////////////////   ITSHERE

    float RES[1][5];
    float HELPER_MATRIX_FOR_PIRAMID[4][5];
    for (int i =0; i <4; i++){
        for (int j=0; j < 5; j++)
        HELPER_MATRIX_FOR_PIRAMID[i][j] = NRM[i][j];
    }
    float TOCHKA_OCHKA[1][4];
    TOCHKA_OCHKA[0][0] = AXC;
    TOCHKA_OCHKA[0][1] = AYC;
    TOCHKA_OCHKA[0][2] = AZC;
    TOCHKA_OCHKA[0][3] = 1;


    cout << "safdsadfsdafadsf" << endl <<  TOCHKA_OCHKA[0][0] << " " << " " << TOCHKA_OCHKA[0][1] << " " << TOCHKA_OCHKA[0][2] << " "  << TOCHKA_OCHKA[0][3] << endl;

    multing_6(TOCHKA_OCHKA, HELPER_MATRIX_FOR_PIRAMID, RES);
    cout << "I FUCK------------=+++++++++++++++++++++++++++++++++++++" << endl;
    for (int i = 0; i < 1; i++) {
        for (int j = 0; j < 5; j++) {
            cout << RES[i][j] << endl;
            if (RES[i][j] < 0) {
                cout << endl << "menshe" << j << endl;
                for (int k = 0; k < 4; k++) NRM[k][j] = NRM[k][j] * (-1);
            }
        }
    }

    float RES_2[1][4];
    float HELPER_MATRIX_FOR_PIRAMID_2[4][4];
    for (int i =0; i <4; i++){
        for (int j=0; j < 4; j++){
        HELPER_MATRIX_FOR_PIRAMID_2[i][j] = NRM[i][j+5];
        cout   << HELPER_MATRIX_FOR_PIRAMID_2[i][j]<<  " ";}
        cout << endl;
    }


    float TOCHKA_OCHKA_2[1][4];
    TOCHKA_OCHKA_2[0][0] = BXC;
    TOCHKA_OCHKA_2[0][1] = BYC;
    TOCHKA_OCHKA_2[0][2] = BZC;
    TOCHKA_OCHKA_2[0][3] = 1;
     cout << "WWWWWWWWWWWWWWWWWWWWWWWWW" << endl <<  TOCHKA_OCHKA_2[0][0] << " " << " " << TOCHKA_OCHKA_2[0][1] << " " << TOCHKA_OCHKA_2[0][2] << " "  << TOCHKA_OCHKA_2[0][3] << endl;
    multing_7(TOCHKA_OCHKA_2, HELPER_MATRIX_FOR_PIRAMID_2, RES_2);

    for (int i=0;i < 1; i++){
        for (int j=0; j<4; j++){
            cout << RES_2[i][j] << endl;
            if (RES_2[i][j] < 0){
                    cout << endl  << "menshe" << j+5 << endl;
                for (int k=0; k <4; k++) NRM[k][j+5] = NRM[k][j+5]*(-1);
            }
        }
    }
}



//----------------------------------------------------------------------------
//========================Painting functions==================================
//----------------------------------------------------------------------------

//
// NOt sure if its okay, but feels like i should do
// all grans in separated func
//

void DRAW_figureA_0(float HP[AN][AM], int COL){
    float TDO[AN][AM]; // TecnicallyDrawingOne
    for (int i = 0; i < AN; i++)
    {
        for (int j = 0; j < AM; j++)
        {
            TDO[i][j] = HP[i][j];
        }
    }
    multing_1(TDO , PROJECTION);
    int poly[10];
    poly[0] = round(TDO[1][0])+SHIFT;    // 1
    poly[1] = round(TDO[1][1])+SHIFT;

    poly[2] = round(TDO[2][0])+SHIFT;    //2
    poly[3] = round(TDO[2][1])+SHIFT;

    poly[4] = round(TDO[3][0])+SHIFT;    //3
    poly[5] = round(TDO[3][1])+SHIFT;

    poly[6] = round(TDO[4][0])+SHIFT;    //4
    poly[7] = round(TDO[4][1])+SHIFT;

    poly[8] = poly[0];
    poly[9] = poly[1];


    setfillstyle(SOLID_FILL, COL);
    setcolor(LIGHTGRAY);
    setbkcolor(WHITE);
    fillpoly(5,poly);

    setcolor(BLACK);
    setfillstyle(SOLID_FILL,WHITE);
}

void DRAW_figureA_1(float HP[AN][AM], int COL){
    float TDO[AN][AM]; // TecnicallyDrawingOne
    for (int i = 0; i < AN; i++)
    {
        for (int j = 0; j < AM; j++)
        {
            TDO[i][j] = HP[i][j];
        }
    }
    multing_1(TDO , PROJECTION);
    int poly[8];
    poly[0] = round(TDO[0][0])+SHIFT;    // 0
    poly[1] = round(TDO[0][1])+SHIFT;

    poly[2] = round(TDO[1][0])+SHIFT;    //1
    poly[3] = round(TDO[1][1])+SHIFT;

    poly[4] = round(TDO[2][0])+SHIFT;    //2
    poly[5] = round(TDO[2][1])+SHIFT;


    poly[6] = poly[0];
    poly[7] = poly[1];


    setfillstyle(SOLID_FILL, COL);
    setcolor(LIGHTGRAY);
    setbkcolor(WHITE);
    fillpoly(4,poly);

    setcolor(BLACK);
    setfillstyle(SOLID_FILL,WHITE);
}

void DRAW_figureA_2(float HP[AN][AM], int COL){
    float TDO[AN][AM]; // TecnicallyDrawingOne
    for (int i = 0; i < AN; i++)
    {
        for (int j = 0; j < AM; j++)
        {
            TDO[i][j] = HP[i][j];
        }
    }
    multing_1(TDO , PROJECTION);
    int poly[10];
    poly[0] = round(TDO[0][0])+SHIFT;    // 0
    poly[1] = round(TDO[0][1])+SHIFT;

    poly[2] = round(TDO[2][0])+SHIFT;    //2
    poly[3] = round(TDO[2][1])+SHIFT;

    poly[4] = round(TDO[3][0])+SHIFT;    //3
    poly[5] = round(TDO[3][1])+SHIFT;

    poly[6] = poly[0];
    poly[7] = poly[1];


    setfillstyle(SOLID_FILL, COL);
    setcolor(LIGHTGRAY);
    setbkcolor(WHITE);
    fillpoly(4,poly);

    setcolor(BLACK);
    setfillstyle(SOLID_FILL,WHITE);
}

void DRAW_figureA_3(float HP[AN][AM], int COL){
    float TDO[AN][AM]; // TecnicallyDrawingOne
    for (int i = 0; i < AN; i++)
    {
        for (int j = 0; j < AM; j++)
        {
            TDO[i][j] = HP[i][j];
        }
    }
    multing_1(TDO , PROJECTION);
    int poly[10];
    poly[0] = round(TDO[0][0])+SHIFT;    // 0
    poly[1] = round(TDO[0][1])+SHIFT;

    poly[2] = round(TDO[3][0])+SHIFT;    //3
    poly[3] = round(TDO[3][1])+SHIFT;

    poly[4] = round(TDO[4][0])+SHIFT;    //4
    poly[5] = round(TDO[4][1])+SHIFT;

    poly[6] = poly[0];
    poly[7] = poly[1];


    setfillstyle(SOLID_FILL, COL);
    setcolor(LIGHTGRAY);
    setbkcolor(WHITE);
    fillpoly(4,poly);

    setcolor(BLACK);
    setfillstyle(SOLID_FILL,WHITE);
}


void DRAW_figureA_4(float HP[AN][AM], int COL){
    float TDO[AN][AM]; // TecnicallyDrawingOne
    for (int i = 0; i < AN; i++)
    {
        for (int j = 0; j < AM; j++)
        {
            TDO[i][j] = HP[i][j];
        }
    }
    multing_1(TDO , PROJECTION);
    int poly[10];
    poly[0] = round(TDO[1][0])+SHIFT;    // 1
    poly[1] = round(TDO[1][1])+SHIFT;

    poly[2] = round(TDO[0][0])+SHIFT;    //0
    poly[3] = round(TDO[0][1])+SHIFT;

    poly[4] = round(TDO[4][0])+SHIFT;    //4
    poly[5] = round(TDO[4][1])+SHIFT;

    poly[6] = poly[0];
    poly[7] = poly[1];


    setfillstyle(SOLID_FILL, COL);
    setcolor(LIGHTGRAY);
    setbkcolor(WHITE);
    fillpoly(4,poly);

    setcolor(BLACK);
    setfillstyle(SOLID_FILL,WHITE);
}

//
//

void DRAW_figureB_0(float HP[BN][BM], int COL){
    float TDO[BN][BM]; // TecnicallyDrawingOne
    for (int i = 0; i < BN; i++)
    {
        for (int j = 0; j < BM; j++)
        {
            TDO[i][j] = HP[i][j];
        }
    }
    multing_2(TDO , PROJECTION);
    int poly[8];
    poly[0] = round(TDO[3][0])+SHIFT;    //3
    poly[1] = round(TDO[3][1])+SHIFT;

    poly[2] = round(TDO[1][0])+SHIFT;    //1
    poly[3] = round(TDO[1][1])+SHIFT;

    poly[4] = round(TDO[2][0])+SHIFT;    //2
    poly[5] = round(TDO[2][1])+SHIFT;

    poly[6] = poly[0];
    poly[7] = poly[1];


    setfillstyle(SOLID_FILL, COL);
    setcolor(LIGHTGRAY);
    setbkcolor(WHITE);
    fillpoly(4,poly);

    setcolor(BLACK);
    setfillstyle(SOLID_FILL,WHITE);
}

void DRAW_figureB_1(float HP[BN][BM], int COL){
    float TDO[BN][BM]; // TecnicallyDrawingOne
    for (int i = 0; i < BN; i++)
    {
        for (int j = 0; j < BM; j++)
        {
            TDO[i][j] = HP[i][j];
        }
    }
    multing_2(TDO , PROJECTION);
    int poly[8];
    poly[0] = round(TDO[0][0])+SHIFT;    // 0
    poly[1] = round(TDO[0][1])+SHIFT;

    poly[2] = round(TDO[1][0])+SHIFT;    //1
    poly[3] = round(TDO[1][1])+SHIFT;

    poly[4] = round(TDO[2][0])+SHIFT;    //2
    poly[5] = round(TDO[2][1])+SHIFT;

    poly[6] = poly[0];
    poly[7] = poly[1];


    setfillstyle(SOLID_FILL, COL);
    setcolor(LIGHTGRAY);
    setbkcolor(WHITE);
    fillpoly(4,poly);

    setcolor(BLACK);
    setfillstyle(SOLID_FILL,WHITE);
}

void DRAW_figureB_2(float HP[BN][BM], int COL){
    float TDO[BN][BM]; // TecnicallyDrawingOne
    for (int i = 0; i < BN; i++)
    {
        for (int j = 0; j < BM; j++)
        {
            TDO[i][j] = HP[i][j];
        }
    }
    multing_2(TDO , PROJECTION);
    int poly[8];
    poly[0] = round(TDO[0][0])+SHIFT;    // 0
    poly[1] = round(TDO[0][1])+SHIFT;

    poly[2] = round(TDO[2][0])+SHIFT;    //2
    poly[3] = round(TDO[2][1])+SHIFT;

    poly[4] = round(TDO[3][0])+SHIFT;    //3
    poly[5] = round(TDO[3][1])+SHIFT;

    poly[6] = poly[0];
    poly[7] = poly[1];


    setfillstyle(SOLID_FILL, COL);
    setcolor(LIGHTGRAY);
    setbkcolor(WHITE);
    fillpoly(4,poly);

    setcolor(BLACK);
    setfillstyle(SOLID_FILL,WHITE);
}

void DRAW_figureB_3(float HP[BN][BM], int COL){
    float TDO[BN][BM]; // TecnicallyDrawingOne
    for (int i = 0; i < BN; i++)
    {
        for (int j = 0; j < BM; j++)
        {
            TDO[i][j] = HP[i][j];
        }
    }
    multing_2(TDO , PROJECTION);
    int poly[8];
    poly[0] = round(TDO[0][0])+SHIFT;    //0
    poly[1] = round(TDO[0][1])+SHIFT;

    poly[2] = round(TDO[1][0])+SHIFT;    //1
    poly[3] = round(TDO[1][1])+SHIFT;

    poly[4] = round(TDO[3][0])+SHIFT;    //3
    poly[5] = round(TDO[3][1])+SHIFT;

    poly[6] = poly[0];
    poly[7] = poly[1];


    setfillstyle(SOLID_FILL, COL);
    setcolor(LIGHTGRAY);
    setbkcolor(WHITE);
    fillpoly(4,poly);

    setcolor(BLACK);
    setfillstyle(SOLID_FILL,WHITE);
}

void Painting_the_figures(float HPA[AN][AM], float HPB[BN][BM], float CAMxNRM_HP[1][9], float LGHxNRM_HP[1][9]){
    cout << endl;
    for (int i =0; i <9 ; i++){
        cout << CAMxNRM_HP[0][i] << " ";
    }
    cout << endl;
    if (CAMxNRM_HP[0][0]>0){
            cout << "0 was painted" << endl;
        if (LGHxNRM_HP[0][0] < 0  && SELFSHADOW ==1)  DRAW_figureA_0(HPA, 7);
       else
       DRAW_figureA_0(HPA, 13);
    }

    if (CAMxNRM_HP[0][1]>0){
            cout << "1 was painted" << endl;
        if (LGHxNRM_HP[0][1] < 0 && SELFSHADOW ==1) DRAW_figureA_1(HPA, 7);
        else
       DRAW_figureA_1(HPA, 9);
    }

    if (CAMxNRM_HP[0][2]>0){
            cout << "2 was painted" << endl;
        if (LGHxNRM_HP[0][2] < 0 && SELFSHADOW ==1) DRAW_figureA_2(HPA, 7);
        else
            DRAW_figureA_2(HPA, 10);
    }

    if (CAMxNRM_HP[0][3]>0){
            cout << "3 was painted" << endl;
        if (LGHxNRM_HP[0][3] < 0 && SELFSHADOW ==1) DRAW_figureA_3(HPA, 7);
        else
            DRAW_figureA_3(HPA, 11);
    }

    if (CAMxNRM_HP[0][4]>0){
            cout << "4 was painted" << endl;
        if (LGHxNRM_HP[0][4] < 0 && SELFSHADOW ==1) DRAW_figureA_4(HPA, 7);
        else
            DRAW_figureA_4(HPA, 12);
    }

    //

}


void Painting_the_figures_2(float HPA[AN][AM], float HPB[BN][BM], float CAMxNRM_HP[1][9], float LGHxNRM_HP[1][9]){

    if (CAMxNRM_HP[0][5]>0){
            cout << "5 was painted" << endl;
        if (LGHxNRM_HP[0][5] < 0 && SELFSHADOW ==1) DRAW_figureB_0(HPB, 8);
        else
            DRAW_figureB_0(HPB, 5);
    }
    if (CAMxNRM_HP[0][6]>0){
            cout << "6 was painted" << endl;
        if (LGHxNRM_HP[0][6] < 0 && SELFSHADOW ==1) DRAW_figureB_1(HPB, 8);
        else
            DRAW_figureB_1(HPB, 4);
    }
    if (CAMxNRM_HP[0][7]>0){
            cout << "7 was painted" << endl;
        if (LGHxNRM_HP[0][7] < 0 && SELFSHADOW ==1) DRAW_figureB_2(HPB, 8);
        else
            DRAW_figureB_2(HPB, 1);
    }
    if (CAMxNRM_HP[0][8]>0){
            cout << "8 was painted" << endl;

        if (LGHxNRM_HP[0][8] < 0 && SELFSHADOW ==1) DRAW_figureB_3(HPB, 8);
        else
            DRAW_figureB_3(HPB, 2);
    }
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
