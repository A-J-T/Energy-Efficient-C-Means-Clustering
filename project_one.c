/*
The data set that we are using has 4 attributes but we are using only 2 attributes.
Those 2 attributes are 1)Study Time 2) Exam Performance.
These 2 attributes will be used to calculate the student's "KnowledgeLevel"
KnowledgeLevel can be High or Low in our program but in the data set "KnowledgeLevel" has High, Low and Middle.
We will represent High as 1 and low as 0. For now we will consider Middle as High so it will be 1.
*/
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
void readDataset(); /*<--- This function reads data set into below arrays.*/
void displayDataset();/*<--- This function will display our data set*/
void startClustering();
void remapSeedValues();
void addToCluster(float,float,float,int);
void displayClusters();
float calculateDistance(float,float,float,float);
int highCluster = 1, lowCluster = 1;
float study_time[260]/*<--- attribute number: 1*/, examPerformance[260]/*<--- attribute number: 2*/, targetAnswers[260]/*<---- real knowledge level: 3*/;
float ourAnswer[258]/*<--- this will store our answer for knowledge level 1 = High, 0 = Low*/;

/*sample seed value to create 2 clusters or knowledge levels*/
/*These seed values will change during different iterations*/
float svLX = 0.2, svLY = 0.2, svHX = 0.78, svHY = 0.78;
float psvLX, psvLY, psvHX, psvHY;
float seedDistance = 0.0;
/*examPerformance is on Y-axis and study_time is on X-axis*/

struct cluster
{
	float study_time;
	float exam_performance;
	float target_value;
}cluster_one[260], cluster_two[250];
int cluster_one_index = 0, cluster_two_index = 0;

int main()
{
	//freopen("output.txt","w",stdout);
	readDataset();
	psvLX = svLX; psvLY = svLY; psvHX = svHX; psvHY = svHY;
	seedDistance = calculateDistance(svLX,svHX,svLY,svHY);
	displayDataset();
	startClustering();
	displayClusters();
	return 0;
}
float calculateDistance(float x1, float x2, float y1,float y2)
{
	return sqrt(((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1)));
}
void addToCluster(float x,float y, float z,int cluster_type)
{
	switch(cluster_type)
	{
		case 1:
			cluster_one[cluster_one_index].study_time = x;
			cluster_one[cluster_one_index].exam_performance = y;
			cluster_one[cluster_one_index++].target_value = z;			
			break;
		case 2:
			cluster_two[cluster_two_index].study_time = x;
			cluster_two[cluster_two_index].exam_performance = y;
			cluster_two[cluster_two_index++].target_value = z;
			break;
		default:
			break;
	}
}
void startClustering()
{
	int counter = 0;
	float distance_1, distance_2;
	cluster_one_index = 0;
	cluster_two_index = 0;
	for(counter = 2;counter<259;counter++)
	{
		distance_1 = calculateDistance(study_time[counter], svHX, examPerformance[counter], svHY);
		distance_2 = calculateDistance(study_time[counter], svLX, examPerformance[counter], svLY);
		
		if((distance_1 <= seedDistance) && (highCluster==1))
		{
			addToCluster(study_time[counter],examPerformance[counter], targetAnswers[counter], 1);
		}
		else if((distance_2 <= seedDistance) && (lowCluster==1))
		{
			addToCluster(study_time[counter],examPerformance[counter], targetAnswers[counter], 2);
		}
	}
	remapSeedValues();
	if(psvHX == svHX && psvHY == svHY)
	{
		printf("\nHigh Knowledge Cluster Seed Value Achieved Successfully.\n");
		highCluster = 0;
	}
	if(psvLX = svLX && psvLY == svLY)
	{
		printf("\nLow Knowledge Cluster Seed Value Achieved Successfully.\n");
		lowCluster = 0;
	}
	if(lowCluster==1 || highCluster==1)
	{
		startClustering();
	}
}
void remapSeedValues()
{
	int counter, count = 0;
	float StudyTime = 0, ExamPerformance = 0;
	psvHX = svHX;
	psvHY = svHY;
	psvLX = svLX;
	psvLY = svLY;
	for(counter=2;counter<260;counter++)
	{
		if(cluster_one[counter].study_time==0 && cluster_one[counter].exam_performance==0)
		{
			break;
		}
		count++;
		StudyTime = cluster_one[counter].study_time + StudyTime;
		ExamPerformance = cluster_one[counter].exam_performance + ExamPerformance;
	}
	svHX = StudyTime/count;
	svHY = ExamPerformance/count;
	ExamPerformance = StudyTime = 0;
	count = 0;
	for(counter=2;counter<260;counter++)
	{
		if(cluster_two[counter].study_time==0 && cluster_two[counter].exam_performance==0)
		{
			break;
		}
		count++;
		StudyTime = cluster_one[counter].study_time + StudyTime;
		ExamPerformance = cluster_one[counter].exam_performance + ExamPerformance;
	}
	svLX = StudyTime/count;
	svLY = ExamPerformance/count;
	printf("\nPrevious Low X: %f\tNew Low X: %f\nPrevious Low Y: %f\tNew Low Y: %f\n",psvLX,svLX,psvLY,svLY);
	printf("\nPrevious High X: %f\tNew High X: %f\nPrevious High Y: %f\tNew High Y: %f\n",psvHX,svHX,psvHY,svHY);
	seedDistance = calculateDistance(svLX,svHX,svLY,svHY);	
	/*count = 0;
	for(counter=2;counter<260;counter++)
	{
		if(cluster_three[counter].study_time==0 && cluster_three[counter].examPerformance==0)
		{
			break;
		}
		count++;
		StudyTime = cluster_one[counter].study_time + StudyTime;
		ExamPerformance = cluster_one[counter].examPerformance + ExamPerformance;
	}*/
}
void readDataset()
{
	FILE *ptr_file;
    char buf[1000];
	ptr_file =fopen("input.txt","r");
    if (!ptr_file)
	{
		printf("Requested Input File Not Found :(");
		return;
	}
	
	int studyTimeIndex = 0, examPerformanceIndex = 0, targetAnswersIndex = 0;
	
	while (fgets(buf,1000, ptr_file)!=NULL)
	{
		int counter;
		char *p = strtok(buf,"\t");
		for(counter = 0;counter<=5 && p!=NULL;counter++)
		{
			if(p!=NULL)
			{
				switch(counter)
				{
					case 0:
						study_time[studyTimeIndex++] = atof(p);
						break;
					case 4:
						examPerformance[examPerformanceIndex++] = atof(p);
						break;
					case 5:
						if(strcmp(p,"High")==0 || strcmp(p,"Middle")==0)
						{
							targetAnswers[targetAnswersIndex++] = 1;
						}
						else
						{
							targetAnswers[targetAnswersIndex++] = 0;
						}
						break;
					default:
						break;
				}
			}
			p = strtok(NULL,"\t");
		}
	}
	fclose(ptr_file);
}
void displayDataset()
{
	printf("\n\nDisplaying Dataset Entries\n\nStudy Time\tExam Performance\tKnowledge Level\n\n");
	int counter = 0;
	for(counter = 0;counter<259;counter++)
	{
		printf("%f\t%f\t\t%f\n",study_time[counter],examPerformance[counter],targetAnswers[counter]);
	}
	printf("\n\nEnd of Displaying Dataset\n\n");
}
void displayClusters()
{
	int counter, total_ones = 0, total_zeroes = 0, total = 0;
	printf("\n\nDisplaying Cluster of Users with High KnowledgeLevel: \nStudy Time\tExam Performance\tTarget Cluster (1: High, 0: Low)\n\n");
	for(counter = 2;counter<260;counter++)
	{
		if(cluster_one[counter].study_time==0 && cluster_one[counter].exam_performance==0)
		{
			break;
		}
		if(cluster_one[counter].target_value==1.0)
		{
			total_ones++;
		}
		if(cluster_one[counter].target_value==0.0)
		{
			total_zeroes++;
		}
		total++;
		printf("%f\t%f\t\t%f\n",cluster_one[counter].study_time, cluster_one[counter].exam_performance, cluster_one[counter].target_value);
	}
	printf("\n\nTotal Entries: %d\tLow Entried: %d\tHigh Entries: %d\n",total,total_zeroes,total_ones);
	printf("-------------------------------------------------------------------------------");
	printf("\n\nDisplaying Cluster of Users with Low KnowledgeLevel: \nStudy Time\tExam Performance\tTarget Cluster (1: High, 0: Low)\n\n");
	total = total_zeroes = total_ones = 0;	
	for(counter = 0;counter<260;counter++)
	{
		if(cluster_two[counter].study_time==0 && cluster_two[counter].exam_performance==0)
		{
			break;
		}
		if(cluster_two[counter].target_value==1.0)
		{
			total_ones++;
		}
		if(cluster_two[counter].target_value==0.0)
		{
			total_zeroes++;
		}
		total++;
		printf("%f\t%f\t\t%f\n",cluster_two[counter].study_time, cluster_two[counter].exam_performance, cluster_two[counter].target_value);
	}
	printf("\n\nTotal Entries: %d\tLow Entried: %d\tHigh Entries: %d\n",total,total_zeroes,total_ones);
	printf("--------------------------------------------------------------------------------");
}
