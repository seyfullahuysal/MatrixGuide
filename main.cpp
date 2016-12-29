#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include <graphics.h> //[2]
#include <dos.h>
#define boyut2 boyut_bul()

#define MAX 16

void matris_al();
void dosya_oku(char[][16][10]);
void simetrik(char[][16][10]);
void dairesel(char matris[][16][10]);
int  mds(char matris[][16][10]);
void hadamard(char matris[][16][10]);
int boyut_bul();
int determinant(int matris[][16],int);
void simetrik_altkare(char matris[][16][10]);
void dairesel_altkare(char matris[][16][10]);
void hadamard_altkare(char matris[][16][10]);

main()
{
    int gd = DETECT, gm;     //detect grafik sürücüsünü otomatik seçer
    initgraph(&gd, &gm, "C:\\TC\\BGI"); // grafik ekranýný baþlattýk 
	system("color 1f");
	matris_al();
	char matris[16][16][10];
	dosya_oku(matris);
	int islem;
	tekrar:printf("\n\n");
	if(boyut2 == 4 || boyut2 == 8 || boyut2 == 16)
	{
		printf("islem yapmak istediginiz secenegi seciniz: \n hadamard()   ->1\n mds()        ->2\n simetrik()   ->3\n dairesel()   ->4 \t : ");scanf("%d",&islem);
	}
	else
	{
	   printf("islem yapmak istediginiz secenegi seciniz: \n  \n mds()          ->2\n simetrik()     ->3\n dairesel()     ->4 \t : ");scanf("%d",&islem);
	}
	switch(islem)
	{
		     case 1:hadamard(matris);hadamard_altkare(matris);break;
     	     case 2:mds(matris);break;
	         case 3:simetrik(matris);simetrik_altkare(matris);break;
	         case 4:dairesel(matris);dairesel_altkare(matris);break;
	         default:printf("1 - 4 arasinda bir deger giriniz...");goto tekrar;
	}
	getch();
    closegraph();

}

void hadamard(char matris[][16][10])
{
	int boyut=boyut_bul();
	int  hadamard=0;

	int bolge1[boyut/2][boyut/2];
	int bolge2[boyut/2][boyut/2];
	int bolge3[boyut/2][boyut/2];
	int bolge4[boyut/2][boyut/2];

	for(int i=0;i<boyut/2;i++)
	{
		for(int j=0;j<boyut/2;j++)
		{
			bolge1[i][j] = atoi(matris[i][j]);
			bolge2[i][j] = atoi(matris[i+(boyut/2)][j]);
			bolge3[i][j] = atoi(matris[i][j+(boyut/2)]);
			bolge4[i][j] = atoi(matris[i+(boyut/2)][j+(boyut/2)]);
		}

	}

	for(int i=0;i<boyut/2;i++)
	{
		for(int j=0;j<boyut/2;j++)
		{
			if(bolge1[i][j] == bolge4[i][j] && bolge2[i][j] == bolge3[i][j])
			{
				hadamard++;
			}
		}
	}


	////////////////////////////////////////////////hadamard
	FILE* dosya;
	    if((dosya=fopen("hadamard.txt","w"))==NULL)
        {

   		printf("dosya acýlamadii..");

	    }
	    else
		{
			if(hadamard== pow(boyut / 2,2))
		{
			fprintf(dosya,"girilen matris hadamard matristir");
		}
		else
		{
			fprintf(dosya,"girilen matris hadamard matris deðildir");
		}
		}



		fclose(dosya);

}


int mds(char matris[][16][10])
{
	int boyut=boyut_bul();
	int matris2[16][16];
	int mdsmi=1;



	 for(int i=2;i<boyut;i++)
    {
        for(int j=0;j<boyut-i+1;j++)
        {
            for(int x=0;x<boyut-i+1;x++)
            {
            	 printf("\n-------------------------------------\n");
                for(int y=0;y<i;y++)
                {

                	printf("| ");
                    for(int z=0;z<i;z++)
                    {

                        matris2[y][z]=atoi(matris[y+j][z+x]);
                        printf(" %d  ",matris2[y][z]);


                    }
                    printf(" |");

                    printf("\n");
                }
                if(determinant(matris2,i)==0)
                {
                	mdsmi=0;
				}
               printf("\nDeterminant = %d",determinant(matris2,i));

            }
        }
    }







    	FILE* dosya;
	    if((dosya=fopen("mds.txt","w"))==NULL)
        {

   		printf("dosya acýlamadii..");

	    }
	    else
		{
			if(mdsmi==1)
		{
			fprintf(dosya,"girilen matris mds matristir");
		}
		else
		{
			fprintf(dosya,"girilen matris mds matris deðildir");
		}

		}



		fclose(dosya);


		return mdsmi;
}
















int determinant(int a[][MAX],int n)   //////// [1]
{
  int det=0,p,h,k,i,j,temp[MAX][MAX];
  if(n==1)
  {
      return a[0][0];
  }
  else if(n==2)
  {
      det=(a[0][0]*a[1][1]-a[0][1]*a[1][0]);
      return det;
  }
  else
  {
    for(p=0;p<n;p++)
    {
       h = 0;
       k = 0;
       for(i=1;i<n;i++)
       {
         for( j=0;j<n;j++)
         {
            if(j==p)
                {
                    continue;
                }
                temp[h][k] = a[i][j];
            k++;
                if(k==n-1)
                {
                      h++;
                      k = 0;
            }
             }
       }
       det=det+a[0][p]*pow(-1,p)*determinant(temp,n-1);
    }
    return det;
  }
}




int boyut_bul()
{

	int boyut=0;
	int okunan;
	char karakter;
	FILE* dosya;
	if((dosya=fopen("matris.txt","r"))==NULL)
     {

   		printf("dosya acýlamadii..");

	}


	else
	{

		karakter=getc(dosya);
		while(karakter!='\n')
		{


			fscanf(dosya,"%d",&okunan);
			boyut++;
			karakter=getc(dosya);


		}

	}

	fclose(dosya);
	return boyut;

}


void matris_al()
{
	FILE *dosya;
	int boyut,gecici;
   	tekrar:
	printf("Boyut Giriniz: ");
	scanf("%d",&boyut);


	if(boyut>=2 && boyut<=16)
	{

			if((dosya=fopen("matris.txt","w"))==NULL)
 			 {

    			printf("dosya acýlamadii..");

			}




			else
			{



				for(int i=0;i<boyut;i++)
				{

					for(int j=0;j<boyut;j++)
					{

						printf("Matrisin %d-%d. indisli elemanini giriniz: ",i+1,j+1);
						scanf("%d",&gecici);
						fprintf(dosya," %d",gecici);

					}

					fprintf(dosya,"\n");
				}
				fclose(dosya);
			}


	}


	else
     {
     	printf("Hatali giris yaptiniz 4-16 arasinda giris yapiniz...\n\n");
		goto tekrar;
	 }



}

void dosya_oku(char matris[][16][10])
{

	int boyut=boyut_bul();
	FILE* dosya;
	if((dosya=fopen("matris.txt","r"))==NULL)
     {

   		printf("dosya acýlamadii..");

	}


	else
	{



		for(int i=0;i<boyut;i++)
		{
			for(int j=0;j<boyut;j++)
			{

				fscanf(dosya,"%s",&matris[i][j]);

			}
		}


	}


fclose(dosya);

}






void simetrik(char matris[][16][10])
{
	int  simetrikmi=0;
	char matris2[16][16][10];
    int  boyut=boyut_bul();
   /////////////////////////////////////////transpoze bulundu
   for(int i=0;i<boyut;i++)
		{
			for(int j=0;j<boyut;j++)
			{

					strcpy(matris2[j][i],matris[i][j]);

			}
		}



	////////////////////////////////////////////////////////////// karþýlaþtýrma

		 for(int i=0;i<boyut;i++)
		{
			for(int j=0;j<boyut;j++)
			{

					if(strcmp(matris[i][j],matris2[i][j])!=0)
					{
						simetrikmi=1;
					}

			}
		}

		 ////////////////////////////////////////////////////////////////////////////////


		FILE* dosya;
	    if((dosya=fopen("simetrik.txt","w"))==NULL)
        {

   		printf("dosya acýlamadii..");

	    }
	    else
		{
			if(simetrikmi==0)
		{
			fprintf(dosya,"girilen matris simetrik matristir\n\n");
		}
		else
		{
			fprintf(dosya,"girilen matris simetrik matris deðildir");
		}
		}



		fclose(dosya);


}

void dairesel(char matris[][16][10])
{
	int boyut=boyut_bul();
	int daireselmi=0;




	int sayac=0,sayac2=0,sayac3=sayac;

	while(sayac!=boyut-1)
	{

		while(sayac2!=boyut-1)
		{


			if(strcmp(matris[0][sayac],matris[sayac2][sayac3])!=0)
			{
				daireselmi=1;
			}

			sayac3++;
			sayac3=sayac3%boyut;
			sayac2++;
		}

		sayac2=0;
		sayac++;
		sayac3=sayac;
	}






		//////////////////////////////////////////////////////////////////////////////////////777



		FILE* dosya;
	    if((dosya=fopen("dairesel.txt","w"))==NULL)
        {

   		printf("dosya acýlamadii..");

	    }
	    else
		{
			if(daireselmi==0)
		{
			fprintf(dosya,"girilen matris dairesel matristir");
		}
		else
		{
			fprintf(dosya,"girilen matris dairesel matris deðildir");
		}
		}



		fclose(dosya);



}
void simetrik_altkare(char matris[][16][10])
{
	 FILE* dosya;
	 int boyut=boyut_bul();
	 int simetrikmi=0;
	 char matris2[16][16][10];
	 char matris3[16][16][10];

	  if((dosya=fopen("simetrik.txt","a"))==NULL)
        {

   			printf("dosya acýlamadii..");

	    }

	 else
	 {
	fprintf(dosya,"\n\n");fprintf(dosya," ");
	 for(int i=2;i<boyut;i++)
    {
        for(int j=0;j<boyut-i+1;j++)
        {
            for(int x=0;x<boyut-i+1;x++)
            {
            	 printf("\n-------------------------------------\n");
                for(int y=0;y<i;y++)
                {

                	printf("| ");
                    for(int z=0;z<i;z++)
                    {

                        strcpy(matris3[y][z],matris[y+j][z+x]);
                        printf(" %s  ",matris3[y][z]);



                    }
                    printf(" |");
                    printf("\n");
                }



 				for(int a=0;a<i;a++)
				{
					for(int b=0;b<i;b++)
					{

						strcpy(matris2[b][a],matris3[a][b]);

					}
				}



	////////////////////////////////////////////////////////////// karþýlaþtýrma
			simetrikmi=0;
			 for(int a=0;a<i;a++)
				{
					for(int b=0;b<i;b++)
					{

						if(strcmp(matris3[a][b],matris2[a][b])!=0)
						{
							simetrikmi=1;
						}



				}
			}



			if(simetrikmi==0)
			{

            printf("simetrik alt kare matris...");


			 for(int a=0;a<i;a++)
				{
					for(int b=0;b<i;b++)
					{

						fprintf(dosya," %s",matris2[a][b]);

					}

					fprintf(dosya,"\n ");
			}

				fprintf(dosya,"\n ");






			}


















            }
        }
    }



	 }









		fclose(dosya);





}
void dairesel_altkare(char matris[][16][10])
{

		FILE* dosya;
		int boyut=boyut_bul();
		int daireselmi=0;
		char matris3[16][16][10];




		if((dosya=fopen("dairesel.txt","a"))==NULL)
        {

   		printf("dosya acýlamadii..");

	    }




	    else
		{
			fprintf(dosya,"\n");
			fprintf(dosya," ");
			for(int i=2;i<boyut;i++)
        {
        for(int j=0;j<boyut-i+1;j++)
        {
            for(int x=0;x<boyut-i+1;x++)
            {
            	 printf("\n-------------------------------------\n");
                for(int y=0;y<i;y++)
                {

                	printf("| ");
                    for(int z=0;z<i;z++)
                    {

                        strcpy(matris3[y][z],matris[y+j][z+x]);
                        printf(" %s  ",matris3[y][z]);


                    }
                    printf(" |");

                    printf("\n");
                }
                //////////////////////////
                int sayac=0,sayac2=0,sayac3=sayac,daireselmi=0;

       for(int a=0;a<i;a++)
       {
       	for(int b=0;b<i;b++)
       	{
       		while(sayac!=boyut-1)
	    {

		daireselmi=0;

		while(sayac2!=boyut-1)
		{


			if(strcmp(matris3[0][sayac],matris3[sayac2][sayac3])!=0)
			{
				daireselmi=1;

			}

			sayac3++;
			sayac3=sayac3%boyut;
			sayac2++;
		}

		sayac2=0;
		sayac++;
		sayac3=sayac;
	   }
		   }
	   }

       if(daireselmi==1)
           {
              for(int a=0;a<i;a++)
             	{
       		        for(int b=0;b<i;b++)
       		         {
       			        fprintf(dosya," %s",matris3[a][b]);
			         }
			         	fprintf(dosya,"\n ");
		        }
		        	fprintf(dosya,"\n ");
	       }


        }
        }
    }

		}



		fclose(dosya);
}
void hadamard_altkare(char matris[][16][10])
{
	 FILE* dosya;
	 int boyut=boyut_bul();
	 int hadamardmi=0;
	 char matris2[16][16][10];
	 char matris3[16][16][10];

	  if((dosya=fopen("hadamard.txt","a"))==NULL)
        {

   			printf("dosya acýlamadii..");

	    }

	 else
	 {
	fprintf(dosya,"\n\n");fprintf(dosya," ");
	 for(int i=2;i<boyut-1;i=i*i)
    {
        for(int j=0;j<boyut-i+1;j++)
        {
            for(int x=0;x<boyut-i+1;x++)
            {
            	 printf("\n-------------------------------------\n");
                for(int y=0;y<i;y++)
                {

                	printf("| ");
                    for(int z=0;z<i;z++)
                    {

                        strcpy(matris3[y][z],matris[y+j][z+x]);
                        printf(" %s  ",matris3[y][z]);



                    }
                    printf(" |");
                    printf("\n");
                }



 				for(int a=0;a<i;a++)
				{
					for(int b=0;b<i;b++)
					{

						strcpy(matris2[b][a],matris3[a][b]);

					}
				}



	////////////////////////////////////////////////////////////// karþýlaþtýrma
			hadamardmi=0;
			 for(int a=0;a<i;a++)
				{
					for(int b=0;b<i;b++)
					{

						if(strcmp(matris3[a][b],matris2[a][b])!=0)
						{
							hadamardmi=1;
						}



				}
			}



			if(hadamardmi==0)
			{

            printf("hadamard alt kare matris...");


			 for(int a=0;a<i;a++)
				{
					for(int b=0;b<i;b++)
					{

						fprintf(dosya," %s",matris2[a][b]);

					}

					fprintf(dosya,"\n ");
			}

				fprintf(dosya,"\n ");






			}


















            }
        }
    }



	 }









		fclose(dosya);





}

