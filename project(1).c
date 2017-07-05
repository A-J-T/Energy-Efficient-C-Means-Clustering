#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<string.h>
void readDataset(); /*<--- This function reads data set into below arrays.*/
void displayDataset();/*<--- This function will display our data set*/
void startClustering();
void displayClusters();
float calculateDistance(float,float,float,float);

struct cluster
{
	char description[100];
	int quantity;
	float price;
}cluster_one[45222], cluster_two[45222], cluster_three[45222], set[45222];
int cluster_one_index = 0, cluster_two_index = 0, cluster_three_index = 0;

int main()
{
	freopen("output.txt","w",stdout);
	readDataset();
	//seedDistance = calculateDistance(svLX,svHX,svLY,svHY);
	displayDataset();
	//startClustering();
	//displayClusters();
}/*
float calculateDistance(float x1, float x2, float y1,float y2)
{
	return sqrt(((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1)));
}*/
void addToCluster(float x,float y,int cluster_type)
{
	switch(cluster_type)
	{
		case 1:
			cluster_one[cluster_one_index].quantity = x;
			cluster_one[cluster_one_index++].price = y;
			break;
		case 2:
			cluster_two[cluster_two_index].quantity = x;
			cluster_two[cluster_two_index++].price = y;
			break;
		case 3:
			cluster_three[cluster_three_index].quantity = x;
			cluster_three[cluster_three_index++].price = y;
		default:
			break;
	}
}/*
void startClustering()
{
	int counter = 0, clusterType = 0;
	float distance_1, distance_2;
	for(counter = 2;counter<259;counter++)
	{
		distance_1 = calculateDistance(set[counter].quantity, svHX, set[counter].price, svHY);
		distance_2 = calculateDistance(set[counter].quantity, svLX, set[counter].price, svLY);
		
		if(distance_1 <= seedDistance)
		{
			clusterType = 1;		
		}
		else if(distance_2 <= seedDistance)
		{
			clusterType = 2;		
		}
		else if(distance_3 <= seedDistance)
		{
			clusterType = 3;
		}
		addToCluster(set[counter].quantity,set[counter].price,clusterType);
	}
}*/
void readDataset()
{
	FILE *ptr_file;
    char buf[1000];
	ptr_file =fopen("ORFinal.txt","r");
    if (!ptr_file)
	{
		printf("Requested Input File Not Found :(");
		return;
	}
	
	int setIndex = 0;
	int count = 0;
	while (fgets(buf,100, ptr_file)!=NULL)
	{
		int counter;
		char *p = strtok(buf,"\t");
		printf("0\t %s\n",p);
		if(strcmp(p,"")==0)
		{
			break;
		}
		count++;
		for(counter = 0;counter<=2 && p!=NULL;counter++)
		{
			printf("\nP: %s\n",p);
			if(p!=NULL&&strcmp(p,"")!=0)
			{
				switch(counter)
				{
					case 0:
						strcpy(set[setIndex].description,p);
						break;
					case 1:
						//printf("P: %s\n",p);
						set[setIndex].quantity = atoi(p);					
						break;
					case 2:
						set[setIndex++].price = atof(p);				
						break;
					default:
						break;
				}
			}
			p = strtok(NULL,"\t");
		}
	}
	fclose(ptr_file);
	printf("\nCount: %d\n",count);
}
void displayDataset()
{
	printf("\n\nDisplaying Dataset Entries\n\nItem Quantity\tItem Price\n");
	int counter = 0;
	for(counter = 0;counter<45222;counter++)
	{
		if(set[counter].price==0 && set[counter].quantity==0)
		{
			break;
		}
		printf("%d\t%f\t\n",set[counter].quantity,set[counter].price);
	}
	printf("\n\nEnd of Displaying Dataset\n\n");
}/*
void displayClusters()
{
	int counter;
	printf("\n\nDisplaying Cluster of Items with Low Price and Quantity: \nQuantity\tPrice\n\n");
	for(counter = 2;counter<45222;counter++)
	{
		if(cluster_one[counter].price==0 && cluster_one[counter].quantity==0)
		{
			break;
		}
		printf("%d\t%f\n",cluster_one[counter].quantity, cluster_one[counter].price);
	}
	printf("-------------------------------------------------------------------------------");
	printf("\n\nDisplaying Cluster of Items with Low Price and Quantity: \nQuantity\tPrice\n\n");
	for(counter = 0;counter<45222;counter++)
	{
		if(cluster_two[counter].price==0 && cluster_two[counter].quantity==0)
		{
			break;
		}
		printf("%d\t%f\n",cluster_two[counter].quantity, cluster_two[counter].price);
	}
	printf("-------------------------------------------------------------------------------");
	printf("\n\nDisplaying Cluster of Items with Low Price and Quantity: \nQuantity\tPrice\n\n");
	for(counter = 0;counter<45222;counter++)
	{
		if(cluster_three[counter].price==0 && cluster_three[counter].quantity==0)
		{
			break;
		}
		printf("%d\t%f\n",cluster_three[counter].quantity, cluster_three[counter].price);
	}
	printf("-------------------------------------------------------------------------------");
}*/
