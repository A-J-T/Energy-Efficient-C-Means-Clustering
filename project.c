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
#include<limits.h>
void initialize();
void readDataset(); /*<--- This function reads data set into below arrays.*/
void displayDataset();/*<--- This function will display our data set*/
void startClustering();
void displayClusters();
int minimumDistance(float,float,float,float);
float calculateDistance(float,float,float,float);

float study_time[260]/*<--- attribute number: 1*/, examPerformance[260]/*<--- attribute number: 2*/, targetAnswers[260]/*<---- real knowledge level: 3*/;
float ourAnswer[258]/*<--- this will store our answer for knowledge level 1 = High, 0 = Low*/;

/*sample seed value to create 2 clusters or knowledge levels*/
/*These seed values will change during different iterations*/
float svLX = 0.2, svLY = 0.2, svHX = 0.75, svHY = 0.75, svVLX = 0.1, svVLY = 0.1, svMX = 0.37, svMY = 0.37;
//float seedDistance_1 = 0.0, seedDistance_2, seedDistance_3, seedDistance_4;
/*examPerformance is on Y-axis and study_time is on X-axis*/
int c;
struct cluster
{
	float study_time;
	float exam_performance;
}cluster_one[260], cluster_two[250], cluster_three[260], cluster_four[260];
int cluster_one_index = 0, cluster_two_index = 0, cluster_three_index = 0, cluster_four_index = 0;

int main()
{
	freopen("output.txt","w",stdout);
	initialize();
	readDataset();
	displayDataset();
	startClustering();
	displayClusters();
}
void initialize()
{
	printf("Enter number of clusters: (min: 2, max: 4): ");
	scanf("%d",&c);
	if(!(c>1&&c<=4)){
		printf("\nIncorrect Value for number of clusters :(\n");
		initialize();
	}
}
float calculateDistance(float x1, float x2, float y1,float y2)
{
	return sqrt(((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1)));
}
int minimumDistance(float a,float b,float c,float d)
{
    if(a<b && a<c && a<d)
        return 1;
    else if(b<a && b<c && b<d)
        return 2;
    else if(c<a && c<b && c<d)
        return 3;
    else if(d<a && d<b && d<c)
        return 4;
}
void addToCluster(float x,float y,int cluster_type)
{
	switch(cluster_type)
	{
		case 1:
			cluster_one[cluster_one_index].study_time = x;
			cluster_one[cluster_one_index++].exam_performance = y;
			break;
		case 2:
			cluster_two[cluster_two_index].study_time = x;
			cluster_two[cluster_two_index++].exam_performance = y;
			break;
		case 3:
			cluster_three[cluster_three_index].study_time = x;
			cluster_three[cluster_three_index++].exam_performance = y;
			break;
		case 4:
			cluster_four[cluster_four_index].study_time = x;
			cluster_four[cluster_four_index++].exam_performance = y;
			break;
		default:
			break;
	}
}
void startClustering()
{
	int counter = 0;
	float distance_1, distance_2, distance_3, distance_4;
	for(counter = 2;counter<259;counter++)
	{
		switch(c)
		{
			case 4:
			{
				distance_1 = calculateDistance(study_time[counter], svHX, examPerformance[counter], svHY);
				distance_2 = calculateDistance(study_time[counter], svMX, examPerformance[counter], svMY);
				distance_3 = calculateDistance(study_time[counter], svLX, examPerformance[counter], svLY);
				distance_4 = calculateDistance(study_time[counter], svVLX, examPerformance[counter], svVLY);
				//printf("%f\t%f\t%f\t%f\n",distance_1,distance_2,distance_3,distance_4);
				int clusterType = minimumDistance(distance_1,distance_2, distance_3, distance_4);

				switch(clusterType)
				{
				    case 1:
                        addToCluster(study_time[counter], examPerformance[counter], 1);
                        break;
					case 2:
                        addToCluster(study_time[counter], examPerformance[counter], 2);
                        break;
					case 3:
                        addToCluster(study_time[counter], examPerformance[counter], 3);
                        break;
                    case 4:
                        addToCluster(study_time[counter], examPerformance[counter], 4);
                        break;
                }
				break;
			}
			case 3:
			{
				distance_1 = calculateDistance(study_time[counter], svHX, examPerformance[counter], svHY);
				distance_2 = calculateDistance(study_time[counter], svMX, examPerformance[counter], svMY);
				distance_3 = calculateDistance(study_time[counter], svLX, examPerformance[counter], svLY);
				int clusterType = minimumDistance(distance_1,distance_2, distance_3, INT_MAX);

				switch(clusterType)
				{
				    case 1:
                        addToCluster(study_time[counter], examPerformance[counter], 1);
                        break;
					case 2:
                        addToCluster(study_time[counter], examPerformance[counter], 2);
                        break;
					case 3:
                        addToCluster(study_time[counter], examPerformance[counter], 3);
                        break;
                }
				break;
			}
			case 2:
			{
				distance_1 = calculateDistance(study_time[counter], svHX, examPerformance[counter], svHY);
				distance_3 = calculateDistance(study_time[counter], svLX, examPerformance[counter], svLY);
				int clusterType = minimumDistance(distance_1,distance_3, INT_MAX, INT_MAX);

				switch(clusterType)
				{
				    case 1:
                        addToCluster(study_time[counter], examPerformance[counter], 1);
                        break;
					case 2:
                        addToCluster(study_time[counter], examPerformance[counter], 2);
                        break;
                }
				break;
			}
		}
	}
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
						if(strcmp(p,"High")==0)
						{
							targetAnswers[targetAnswersIndex++] = 1;
						}
						else if(strcmp(p,"Middle")==0)
						{
							targetAnswers[targetAnswersIndex++] = 2;
						}
						else if(strcmp(p,"Low")==0)
                        {
                            targetAnswers[targetAnswersIndex++] = 3;
                        }
                        else if(strcmp(p,"very_low")==0)
                        {
                            targetAnswers[targetAnswersIndex++] = 4;
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
	int counter;
	if(c == 2)
	{
		printf("\n\nDisplaying Cluster of Users with High KnowledgeLevel: \nStudy Time\tExam Performance\n\n");
		for(counter = 2;counter<259;counter++)
		{
			printf("%f\t%f\n",cluster_one[counter].study_time, cluster_one[counter].exam_performance);
		}
		printf("-------------------------------------------------------------------------------");
		printf("\n\nDisplaying Cluster of Users with Low KnowledgeLevel: \nStudy Time\tExam Performance\n\n");
		for(counter = 0;counter<260;counter++)
		{
			printf("%f\t%f\n",cluster_two[counter].study_time, cluster_two[counter].exam_performance);
		}
		printf("-------------------------------------------------------------------------------");
	}
	else if(c == 3)
	{
		printf("\n\nDisplaying Cluster of Users with High KnowledgeLevel: \nStudy Time\tExam Performance\n\n");
		for(counter = 2;counter<259;counter++)
		{
			printf("%f\t%f\n",cluster_one[counter].study_time, cluster_one[counter].exam_performance);
		}
		printf("-------------------------------------------------------------------------------");
		printf("\n\nDisplaying Cluster of Users with Middle KnowledgeLevel: \nStudy Time\tExam Performance\n\n");
		for(counter = 0;counter<260;counter++)
		{
			printf("%f\t%f\n",cluster_two[counter].study_time, cluster_two[counter].exam_performance);
		}
		printf("-------------------------------------------------------------------------------");
		printf("\n\nDisplaying Cluster of Users with Low KnowledgeLevel: \nStudy Time\tExam Performance\n\n");
		for(counter = 0;counter<260;counter++)
		{
			printf("%f\t%f\n",cluster_three[counter].study_time, cluster_three[counter].exam_performance);
		}
		printf("-------------------------------------------------------------------------------");
	}
	else if(c == 4)
	{
		printf("\n\nDisplaying Cluster of Users with High KnowledgeLevel: \nStudy Time\tExam Performance\n\n");
		for(counter = 2;counter<259;counter++)
		{
			printf("%f\t%f\n",cluster_one[counter].study_time, cluster_one[counter].exam_performance);
		}
		printf("-------------------------------------------------------------------------------");
		printf("\n\nDisplaying Cluster of Users with Middle KnowledgeLevel: \nStudy Time\tExam Performance\n\n");
		for(counter = 0;counter<260;counter++)
		{
			printf("%f\t%f\n",cluster_two[counter].study_time, cluster_two[counter].exam_performance);
		}
		printf("-------------------------------------------------------------------------------");
		printf("\n\nDisplaying Cluster of Users with Low KnowledgeLevel: \nStudy Time\tExam Performance\n\n");
		for(counter = 2;counter<259;counter++)
		{
			printf("%f\t%f\n",cluster_three[counter].study_time, cluster_three[counter].exam_performance);
		}
		printf("-------------------------------------------------------------------------------");
		printf("\n\nDisplaying Cluster of Users with Very Low KnowledgeLevel: \nStudy Time\tExam Performance\n\n");
		for(counter = 0;counter<260;counter++)
		{
			printf("%f\t%f\n",cluster_four[counter].study_time, cluster_four[counter].exam_performance);
		}
		printf("-------------------------------------------------------------------------------");
	}
}
