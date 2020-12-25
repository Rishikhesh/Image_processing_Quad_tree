//IN THIS PACKAGE WE HAVE TRIED TO GIVE A COMPACT REPRESENTATION FOR AN IMAGE USING QUAD TREE AND PERFORM OPERATIONS VIEW , CUT AND ZOOM ON IT
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<conio.h>
using namespace std;
int picture[256][256];
int Array[256][256],Size=256;
struct QuadTree
{
    int pixel;
    QuadTree *topright,*topleft,*bottomright,*bottomleft;
};

QuadTree *root=NULL;

QuadTree *allocate()                                        //THIS FUNCTION ALLOCATES MEMORY FOR A NODE DYNAMICALLY
{
    QuadTree *temp=new QuadTree;
    temp->pixel=-1;
    temp->topright=temp->topleft=temp->bottomright=temp->bottomleft=NULL;
    return temp;
}

void ReadImage()                                            //THIS FUNCTION READS THE PIXEL VALUE INTO AN ARRAY FROM A FILE
{
    int val;
    ifstream fin("image.txt",ios::in);
    if(!fin)
    {
        cout<<"\nError!";
        exit(0);
    }
    else
    {
        for(int i=0;i<256;i++)
        {
            for(int j=0;j<256;j++)
            {
                fin>>val;
                picture[i][j]=val;
            }
        }
    }
    fin.close();
}

QuadTree *Insert(int x1,int x2,int y1,int y2)               //THIS FUNCTION GIVES THE QUADTREE FOR THE ARRAY
{
    int Mid1,Mid2,Pixel,Flag=0,i,j;
    Pixel=picture[x1][y1];
    if(x1<x2 && y1<y2)
    {

        {
            Mid1=(x1+x2)/2;
            Mid2=(y1+y2)/2;
            QuadTree *temp=new QuadTree;
            temp->pixel=-1;
            temp->topright = Insert(x1,Mid1,Mid2+1,y2);
            temp->topleft  = Insert(x1,Mid1,y1,Mid2);
            temp->bottomleft = Insert(Mid1+1,x2,y1,Mid2);
            temp->bottomright = Insert(Mid1+1,x2,Mid2+1,y2);
            return temp;
        }
    }
    else if(x1==x2 && y1==y2)
    {
        QuadTree *temp=new QuadTree;
        temp->pixel=Pixel;
        temp->topright=NULL;
        temp->topleft=NULL;
        temp->bottomleft=NULL;
        temp->bottomright=NULL;
        return temp;
    }
}

void Retrieval(QuadTree *ptr,int x1,int x2,int y1,int y2)   //THIS FUNCTION RETRIVES THE ARRAY BACK FROM QUADTREE
{
    int Mid1,Mid2,i,j;
    Mid1=(x1+x2)/2;
    Mid2=(y1+y2)/2;
    int sum = 0;
    if(ptr!=NULL)
    {
        if(ptr->pixel==-1)
        {
            Retrieval(ptr->topright,x1,Mid1,Mid2+1,y2);
            Retrieval(ptr->topleft,x1,Mid1,y1,Mid2);
            Retrieval(ptr->bottomleft,Mid1+1,x2,y1,Mid2);
            Retrieval(ptr->bottomright,Mid1+1,x2,Mid2+1,y2);
        }
        else
        {
            Array[x1][y1]=ptr->pixel;
        }
    }
}

void Cut(QuadTree *ptr)                                     //THIS FUNCTION CUTS THE PORTION SPECIFIED BY THE USER
{
    int choice;
    int x1=0,x2=Size-1,y1=0,y2=Size-1,Mid1,Mid2;
    char ch;
    system("cls");
    for(int i=0;i<=255;i++)
    {
        for(int j=0;j<=255;j++)
        {
            Array[i][j]=255;
        }
    }
    do
    {

        Mid1=(x1+x2)/2;
        Mid2=(y1+y2)/2;
        cout<<endl<<"\t\t**********************************************************************************";
        cout<<endl<<"\t\t**********************************************************************************";
        cout<<endl<<"\t\t**                                                                              **";
        cout<<endl<<"\t\t**                       Portion to cut                                         **";
        cout<<endl<<"\t\t**                        1.top right                                           **";
        cout<<endl<<"\t\t**                        2.top left                                            **";
        cout<<endl<<"\t\t**                        3.bottom left                                         **";
        cout<<endl<<"\t\t**                        4.bottom right                                        **";
        cout<<endl<<"\t\t**                                                                              **";
        cout<<endl<<"\t\t**********************************************************************************";
        cout<<endl<<"\t\t**********************************************************************************";
        cout<<endl<<"\t\tEnter your choice:";
        cin>>choice;
        switch(choice)
        {
            case 1:
                x1=x1;
                x2=Mid1;
                y1=Mid2+1;
                y2=y2;
                ptr=ptr->topright;
                break;
            case 2:
                x1=x1;
                x2=Mid1;
                y1=y1;
                y2=Mid2;
                ptr=ptr->topleft;
                break;
            case 3:
                x1=Mid1+1;
                x2=x2;
                y1=y1;
                y2=Mid2;
                ptr=ptr->bottomleft;
                break;
            case 4:
                x1=Mid1+1;
                x2=x2;
                y1=Mid2+1;
                y2=y2;
                ptr=ptr->bottomright;
                break;
        }
        cout<<"\n Do you wish Cut Further (y/n) ? ";
        cin>>ch;
    }
    while(ch=='y');
    Retrieval(ptr,x1,x2,y1,y2);
}
void Zoom(QuadTree *ptr)                                    //THIS FUNCTION ZOOMS THE PORTION SPECIFIED BY THE USER
{
    int choice;
    int x1=0,x2=Size-1,y1=0,y2=Size-1,Mid1,Mid2;
    char ch;
    system("cls");
    do
    {
        Size=Size/2;

        cout<<endl<<"\t\t**********************************************************************************";
        cout<<endl<<"\t\t**********************************************************************************";
        cout<<endl<<"\t\t**                                                                              **";
        cout<<endl<<"\t\t**                       Portion to zoom                                        **";
        cout<<endl<<"\t\t**                        1.top right                                           **";
        cout<<endl<<"\t\t**                        2.top left                                            **";
        cout<<endl<<"\t\t**                        3.bottom left                                         **";
        cout<<endl<<"\t\t**                        4.bottom right                                        **";
        cout<<endl<<"\t\t**                                                                              **";
        cout<<endl<<"\t\t**********************************************************************************";
        cout<<endl<<"\t\t**********************************************************************************";
        cout<<endl<<"\t\tEnter your choice:";
        cin>>choice;
        switch(choice)
        {
            case 1:
                ptr=ptr->topright;
                break;
            case 2:
                ptr=ptr->topleft;
                break;
            case 3:
                ptr=ptr->bottomleft;
                break;
            case 4:
                ptr=ptr->bottomright;
                break;
        }
        cout<<"\n Do you wish Zoom Further(y/n) ? ";
        cin>>ch;
    }
    while(ch=='y');
    Retrieval(ptr,0,Size-1,0,Size-1);
}
void WriteFile()                                            //THIS FUNCTION WRITES THE PIXEL VALUE INTO A NEW FILE , TO BE DISPLAYED IN MATLAB
{
    ofstream fout("op_pixel.txt",ios::out);
    for(int i=0;i<Size;i++)
    {
        for(int j=0;j<Size;j++)
        {
            fout<<Array[i][j];
            fout<<endl;
        }
    }
}
main()
{
    int choice;
    char ch;
    ReadImage();
    root=Insert(0,255,0,255);
    system("cls");
    do
    {
        cout<<endl<<"\t\t*********************************************************";
        cout<<endl<<"\t\t*********************************************************";
        cout<<endl<<"\t\t**                                                     **";
        cout<<endl<<"\t\t**              1.View image                           **";
        cout<<endl<<"\t\t**              2.Cut one portion                      **";
        cout<<endl<<"\t\t**              3.Zoom In                              **";
        cout<<endl<<"\t\t**                                                     **";
        cout<<endl<<"\t\t*********************************************************";
        cout<<endl<<"\t\t*********************************************************";
        cout<<endl<<"\t\tEnter your choice:";
        cin>>choice;
        switch(choice)
        {
            case 1:
                Retrieval(root,0,255,0,255);
                WriteFile();
                cout<<"Pixel valued file has be produced";
                break;
            case 2:
                Cut(root);
                WriteFile();
                cout<<"Pixel valued file has be produced";
                break;
            case 3:
                Zoom(root);
                WriteFile();
                cout<<"Pixel valued file has be produced";
        }
        cout<<"\nDo you wish to continue(y/n) ? ";
        cin>>ch;
    }while(ch=='y');
}
