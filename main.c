#include "stdio.h"
#include "stdlib.h"
//#include "math.h"
#include "stdbool.h"

int find2Min(int* arrptr, int len)
{
	int j = 0;

	int mins[3];
	int indices[3];

	bool three;

	for(j=0;j<len;j++)
	{
		if (arrptr[j] >= 0)
		{
			mins[0] = arrptr[j];
			indices[0] = j;
			break;
		}	
	}

	for (j=0;j<len;j++)
	{
		if ( arrptr[j] < mins[0] && arrptr[j] >= 0 )
		{
			mins[0] = arrptr[j];
			indices[0] = j;
		}
	}

	for (j=0;j<len;j++)
	{
		if (arrptr[j] >= 0 && j != indices[0] )
		{
			mins[1] = arrptr[j];
			indices[1] = j;
			break;
		}	
	}

	for (j=0;j<len;j++)
	{
		if ( arrptr[j] < mins[1] && j != indices[1] && arrptr[j] >= 0 )
		{
			mins[1] = arrptr[j];
			indices[1] = j;
		}
	}

	three = false;

	for (j=0;j<len;j++)
	{
		if ( arrptr[j] >= 0 && j != indices[0] && j != indices[1] )
		{
			mins[2] = arrptr[j];
			indices[2] = j;
			three = true;
			break;
		}
	}

	if (three == true)
	{
		for (j=0;j<len;j++)
		{
			if (arrptr[j] >= 0 && arrptr[j] < mins[2] && arrptr[j] > mins[0] && j != indices[0] && j != indices[1])
			{
				mins[2] = arrptr[j];
				indices[2] = j;
			}
		}
	}

	if (three == true && mins[1] == mins[0] )
		return abs(mins[2]-mins[0]);
	else
		return abs(mins[1]-mins[0]);	
}

int find1Min(int* arrptr, int len)
{
	int j = 0;
	int min;
	int minpos=0;
	
	for (j=0;j<len;j++)
	{
		if (arrptr[j]>=0)
		{
			min = arrptr[j];
			minpos = j;
			break;
		}
	}
	for (j=0;j<len;j++)
	{
		if ( arrptr[j] < min && arrptr[j] >= 0 && j!=minpos )
		{
			min = arrptr[j];
			minpos = j;
		}
	}

	return minpos;
}

struct cell
{
	int cost;
	bool isbasic;
	int value;
};

struct point
{
	char where;
	int pos;
	int val;
};

int main()
{
	printf("\nВерсия Ясность\n");

	int i = 0;
	int j = 0;

	unsigned int m;
	unsigned int n;
	
	FILE* problem;
	problem = fopen("tpfile.txt","r");

	fscanf(problem, "%d,%d",&m,&n);

	printf("\nВ исходной задаче строк: %d; столбцов: %d;\n",m,n);
	
	int inp_arr[m][n];

	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			fscanf(problem, "%d", &inp_arr[i][j]);
			fseek(problem, 1, SEEK_CUR);
		}
	}

	unsigned int sup[m];
	unsigned int dem[n];

	for(i=0;i<m;i++)
	{
			fscanf(problem, "%d", &sup[i]);
			fseek(problem, 1, SEEK_CUR);
	}

	for(j=0;j<n;j++)
	{
			fscanf(problem, "%d", &dem[j]);
			fseek(problem, 1, SEEK_CUR);
	}

	fclose(problem);
		
	unsigned int sup_sum = 0;
	unsigned int dem_sum = 0;
	
	for(i=0; i<m; i++)
	{
		sup_sum += sup[i];
	}
	
	for(i=0; i<n; i++)
	{
        	dem_sum += dem[i];
	}

	printf("\nМатрица стоимостей:\n");

	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			printf(" %d ", inp_arr[i][j]);
		}
		printf("\n");
	}

	printf("\nБаланс исходной задачи:\nспрос: %d;\nпредложение: %d;\n", sup_sum, dem_sum);

	unsigned int x = n;
	unsigned int y = m;

	if (sup_sum > dem_sum)
	{
		x += 1; 		
	}
	
	if (dem_sum > sup_sum)
	{
		y += 1;
	}

	int matrix[y][x];
	unsigned int modsup[y], moddem[x];

	i = 0;
	for(i=0;i<y;i++)
	{
		for(j=0;j<x;j++)
		{
			if (i<m && j<n)
				matrix[i][j]=inp_arr[i][j];
			else
				matrix[i][j]=0;
		}
	}

	printf("\nСпрос и предложение в сбалансированной задаче:\nпредложение (по строкам):");

	for(i=0;i<y;i++)
	{
		if (i<m) modsup[i] = sup[i];
		else modsup[i] = dem_sum - sup_sum;
		printf("\n%d: %d ", i+1, modsup[i]);
	}

	printf("\nспрос (по столбцам:)");

	for(j=0;j<x;j++)
	{
		if (j<n) moddem[j] = dem[j];
		else moddem[j] = sup_sum - dem_sum;
		printf("\n%d: %d ", j+1, moddem[j]);
	}

	printf("\n\nМатрица стоимостей сбалансированной задачи:\n");

	for(i=0;i<y;i++)
	{
		for(j=0;j<x;j++)
		{
			printf(" %d ", matrix[i][j]);
		}
		printf("\n");
	}

	printf("\nМЕТОД ФОГЕЛЯ\n\n");

	struct cell solutions[y][x];
	for (i=0;i<y;i++)
	{
		for (j=0;j<x;j++)
		{
			solutions[i][j].cost = matrix[i][j];
			solutions[i][j].isbasic = false;
			solutions[i][j].value = 0;
		}
	}

	for(i=0;i<y;i++)
	{
		for(j=0;j<x;j++)
		{
			printf(" %d ", matrix[i][j]);
		}
		printf("\n");
	}

	printf("\n");

	int s_delta[y];
	int d_delta[x];

	bool xignored[x];
	bool yignored[y];

	for (i=0;i<x;i++) xignored[i]=false;
	for (i=0;i<y;i++) yignored[i]=false;

	int xbuff[x];
	int ybuff[y];

	struct point maxdelta;
	int mincostpos;

	int rows = y;
	int cols = x;

	bool chk;

	while (rows > 1 && cols > 1)
	{
		printf("строки:\n");
		for (i=0;i<y;i++)
		{

			if (yignored[i] == true )
			{
				s_delta[i] = -1;
			} 
			else
			{
				for (j=0;j<x;j++)
				{
					xbuff[j] = matrix[i][j];
					printf("[%d]",xbuff[j]);
				}
				s_delta[i] = find2Min(xbuff,x);
				printf(" штраф: %d\n",find2Min(xbuff,x));
			}
		}

		printf("\nстолбцы:\n");

		for (i=0;i<x;i++)
		{

			if (xignored[i] == true)
			{
				d_delta[i] = -1;
			}
			else
			{
				for (j=0;j<y;j++)
				{
					ybuff[j] = matrix[j][i];
					printf("[%d]",ybuff[j]);
				}
				d_delta[i] = find2Min(ybuff,y);
				printf(" штраф: %d\n",find2Min(ybuff,y));
			}
		}
		
		printf("\n");	

		maxdelta.where = 'n';

		for (i=0;i<x;i++)
		{
			if (d_delta[i] != -1)
			{
				maxdelta.where = 'd';
	       			maxdelta.pos = i;
				maxdelta.val = d_delta[i];
				break;
			}
		}

		if (maxdelta.where == 'n')
		{
			for (j=0;j<y;j++)
			{
				if (s_delta[j] != -1)
				{
					maxdelta.where = 's';
	        			maxdelta.pos = j;
					maxdelta.val = s_delta[j];
					break;
				}
			}
		}

		for (i=0;i<y;i++)
		{
			if (s_delta[i] > maxdelta.val)
			{
				maxdelta.val = s_delta[i];
				maxdelta.where = 's';
				maxdelta.pos = i;
			}
		}

		for (i=0;i<x;i++)
		{
			if (d_delta[i] > maxdelta.val)
			{
				maxdelta.val = d_delta[i];
				maxdelta.where = 'd';
				maxdelta.pos = i;
			}
		}
	
		printf("\nНаибольший штраф: %d;\n(информация для отладки:\nгде находится: \"%c\";\nместо в массиве штрафов: %d)",
			maxdelta.val, maxdelta.where, maxdelta.pos+1);

		printf("\n\n");

		mincostpos = 0;

		if (maxdelta.where == 'd')
		{
			for (j=0;j<y;j++)
			{
				ybuff[j] = matrix[j][maxdelta.pos];
				printf("[%d]",ybuff[j]);
			}
			mincostpos = find1Min(ybuff,y);
			printf("\nМинимальная стоимость находится в ячейке %d ",find1Min(ybuff,y)+1);

			solutions[mincostpos][maxdelta.pos].isbasic = true;
			if (modsup[mincostpos] > moddem[maxdelta.pos])
			{
				solutions[mincostpos][maxdelta.pos].value = moddem[maxdelta.pos];
				modsup[mincostpos] -= moddem[maxdelta.pos];
				moddem[maxdelta.pos] = 0;

				for (i=0;i<y;i++)
				{
					matrix[i][maxdelta.pos] = -1;
				}
				xignored[maxdelta.pos] = true;
				cols--;

			}
			else if (modsup[mincostpos] < moddem[maxdelta.pos])
			{
				solutions[mincostpos][maxdelta.pos].value = modsup[mincostpos];
				moddem[maxdelta.pos] -= modsup[mincostpos];
				modsup[mincostpos] = 0;

				for (i=0;i<x;i++)
				{
					matrix[mincostpos][i] = -1;
				}
				yignored[mincostpos] = true;
				rows--;
			}
			else if (modsup[mincostpos] == moddem[maxdelta.pos])
			{
				solutions[mincostpos][maxdelta.pos].value = modsup[mincostpos];
				modsup[mincostpos] = 0;
				moddem[maxdelta.pos] = 0;

				for (i=0;i<y;i++)
				{
					matrix[i][maxdelta.pos] = -1;
				}
				xignored[maxdelta.pos] = true;
				cols--;

			}
			printf("и равна %d;\n\nзначение базисной переменной x[%d;%d] = %d\n\n", 
				solutions[mincostpos][maxdelta.pos].cost,
				mincostpos+1, maxdelta.pos+1,	
				solutions[mincostpos][maxdelta.pos].value);
		}	
		else if (maxdelta.where == 's')
		{
			for (j=0;j<x;j++)
			{
				xbuff[j] = matrix[maxdelta.pos][j];
				printf("[%d]",xbuff[j]);
			}
			mincostpos = find1Min(xbuff,x);
			printf("\nМинимальная стоимость находится в ячейке %d ",find1Min(xbuff,x)+1);
			solutions[maxdelta.pos][mincostpos].isbasic = true;
			if (modsup[maxdelta.pos] > moddem[mincostpos])
			{
				solutions[maxdelta.pos][mincostpos].value = moddem[mincostpos];
				modsup[maxdelta.pos] -= moddem[mincostpos];
				moddem[mincostpos] = 0;
			
				for (i=0;i<y;i++)
				{
					matrix[i][mincostpos] = -1;
				}		
				xignored[mincostpos] = true;
				cols--;
			}
			else if (modsup[maxdelta.pos] < moddem[mincostpos])
			{
				solutions[maxdelta.pos][mincostpos].value = modsup[maxdelta.pos];
				moddem[mincostpos] -= modsup[maxdelta.pos];
				modsup[maxdelta.pos] = 0;

				for (i=0;i<x;i++)
				{
					matrix[maxdelta.pos][i] = -1;
				}
				yignored[maxdelta.pos] = true;
			        rows--;	
			}
			else if (modsup[maxdelta.pos] == moddem[mincostpos])
			{
				solutions[maxdelta.pos][mincostpos].value = modsup[maxdelta.pos];
				modsup[maxdelta.pos] = 0;
				moddem[mincostpos] = 0;

				for (i=0;i<y;i++)
				{
					matrix[i][mincostpos] = -1;
				}	
				xignored[mincostpos] = true;
				cols--;
			}
			printf("и равна %d;\n\nзначение базисной переменной x[%d;%d] = %d\n\n",  
				solutions[maxdelta.pos][mincostpos].cost, 
				maxdelta.pos+1, mincostpos+1,
				solutions[maxdelta.pos][mincostpos].value);
		}

		for(i=0;i<y;i++)
		{
			for(j=0;j<x;j++)
			{
				printf(" %d ", matrix[i][j]);
			}
			printf("\n");		
		}
		printf("\n");
	}

	printf("\nМЕТОД НАИМЕНЬШЕЙ СТОИМОСТИ\n\n");

	char dir;
	int notignored=0;

	while (rows>0 && cols>0)
	{
		i = 0;
		for(j=0;j<y;j++)
		{
			if(yignored[j]==true)
				i++;
		}

		if(i==(y-1))
		{
			dir = 'l';
			for(j=0;j<y;j++)
			{
				if(yignored[j]==false)
					notignored = j;				
			}
			for(j=0;j<x;j++)
			{
				xbuff[j] = matrix[notignored][j];
				mincostpos = find1Min(xbuff, x);
			}
		}
		else
		{
			dir = 'c';
			for(j=0;j<x;j++)
			{
				if(xignored[j]==false)
				notignored = j;				
			}
			for(j=0;j<y;j++)//
			{
				ybuff[j] = matrix[j][notignored];
				mincostpos = find1Min(ybuff, y);
			}
		}
	
		if (dir =='l')
		{
			if (modsup[notignored] > moddem[mincostpos])
			{
				solutions[notignored][mincostpos].value=moddem[mincostpos];
				solutions[notignored][mincostpos].isbasic=true;			
				modsup[notignored]-=moddem[mincostpos];
				moddem[mincostpos]=0;
				xignored[mincostpos] = true;
				matrix[notignored][mincostpos]=-1;
			}
			else if (modsup[notignored] <  moddem[mincostpos])
			{
				solutions[notignored][mincostpos].value=modsup[notignored];
				solutions[notignored][mincostpos].isbasic=true;	
				modsup[notignored]=0;
				moddem[mincostpos]-=modsup[notignored];
				yignored[notignored] = true;
				matrix[notignored][mincostpos]=-1;
			}
			else if (modsup[notignored] = moddem[mincostpos])
			{
				solutions[notignored][mincostpos].value=moddem[mincostpos];
				solutions[notignored][mincostpos].isbasic=true;			
				modsup[notignored]-=moddem[mincostpos];
				moddem[mincostpos]=0;
				xignored[mincostpos] = true;
				matrix[notignored][mincostpos]=-1;
			}
			cols--;

			printf("Базисная переменная x[%d;%d] = %d;\n\n", 
				notignored+1, mincostpos+1, solutions[notignored][mincostpos].value);
		}

		else if (dir =='c')
		{
			if (modsup[mincostpos] > moddem[notignored])
			{
				solutions[mincostpos][notignored].value=moddem[notignored];
				solutions[mincostpos][notignored].isbasic=true;	
				modsup[mincostpos]-=moddem[notignored];
				moddem[notignored]=0;
				xignored[notignored] = true;
				matrix[mincostpos][notignored]=-1;
			}
			else if (modsup[mincostpos] <  moddem[notignored])
			{
				solutions[mincostpos][notignored].value=modsup[mincostpos];
				solutions[mincostpos][notignored].isbasic=true;			
				modsup[mincostpos]=0;
				moddem[notignored]-=modsup[mincostpos];
				yignored[mincostpos] = true;
				matrix[mincostpos][notignored]=-1;
			}
			else if (modsup[mincostpos] = moddem[notignored])
			{
				solutions[mincostpos][notignored].value=moddem[notignored];
				solutions[mincostpos][notignored].isbasic=true;		
				modsup[mincostpos]-=moddem[notignored];
				moddem[notignored]=0;
				xignored[notignored] = true;
				matrix[mincostpos][notignored]=-1;
			}
			rows--;

			printf("Базисная переменная x[%d;%d] = %d;\n\n", 
				 mincostpos+1, notignored+1, solutions[mincostpos][notignored].value);
		}
		
		if (rows==0 || cols==0)
		{
			rows = 0;
			cols = 0;
		}

		for(i=0;i<y;i++)
		{
			for(j=0;j<x;j++)
			{
				printf(" %d ", matrix[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}

	printf("\nРЕЗУЛЬТАТ\n\nМатрица значений переменных:\n");

	for(i=0;i<y;i++)
	{
		for(j=0;j<x;j++)
		{
			printf(" %d ", solutions[i][j].value);
		}
		printf("\n");
	}
	printf("\n\nБазисные (1) и небазисные (0) переменные:\n");

	for(i=0;i<y;i++)
	{
		for(j=0;j<x;j++)
		{
			printf(" %d ", solutions[i][j].isbasic);
		}
		printf("\n");
	}
	printf("\n\nСтоимости:\n");

	for(i=0;i<y;i++)
	{
		for(j=0;j<x;j++)
		{
			printf(" %d ", solutions[i][j].cost);
		}
		printf("\n");
	}
	printf("\n");

	return 0;
}