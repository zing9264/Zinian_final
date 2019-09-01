#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define neuron1 32
#define inputw "merge.txt"

int main(){	

	//load ans//
	int ans[10000];
	FILE *fp;
	int i, j, t;
	fp = fopen("test_data/ans.txt", "r");
	if (fp==NULL){
		puts("ERROR: read answer.");
		exit(-1);
	}
	for (i=0;i<10000;i++)
		fscanf(fp, "%d", &ans[i]);
	fclose(fp);

	//load w/b //
	float w_h1[neuron1][784];   
	float w_o[10][neuron1];
	float b_h1[neuron1];
	float b_o[10];
	
	fp = fopen(inputw, "r");
	if (fp==NULL){
		puts("ERROR: read model.");
		exit(-1);
	}
	for (i=0;i<neuron1;i++)
		for (j=0;j<784;j++){
			fscanf(fp, "%x", &w_h1[i][j]);	
			//printf(" w_h1[i][j]  : %f\n", w_h1[i][j]);
		}
				
	for (i=0;i<neuron1;i++)
		fscanf(fp, "%x", &b_h1[i]);	
	for (i=0;i<10;i++)
		for (j=0;j<neuron1;j++)
			fscanf(fp, "%x", &w_o[i][j]);				
	for (i=0;i<10;i++)
		fscanf(fp, "%x", &b_o[i]);	
	fclose(fp);

	float v_h1[neuron1];
	float results[10];
	int input[784];
	float inputf[784];
	char filename[16];
	char tmp[4][16];
	float max,correct=0;
	int max_idx;
	int total=0;

	for (t=0;t<10000;t++){
		
		//load input//
		sprintf(filename, "test_data/%05d.ppm", t);
		fp = fopen(filename, "r");
		if (fp==NULL){
			puts("err input");
			return 0;
		}
		fscanf(fp, "%s %s %s %s", tmp[0], tmp[1], tmp[2], tmp[3]); // Skip first 4 values.
		for (i=0;i<784;i++){
			fscanf(fp, "%d", &input[i]);
		}
		fclose(fp);

		//convert input//
		for (i=0;i<784;i++){
			input[i] = 255 - input[i];	
			inputf[i] = ((float)input[i]) * (1.0/255.0);
		}
	
		//DNN inference stage- hidden layer//
		for (i=0;i<neuron1;i++){
			v_h1[i] = 0.0;
			for (j=0;j<784;j++){
				v_h1[i] += inputf[j]*w_h1[i][j];	
			}
			v_h1[i] += b_h1[i];
			if(v_h1[i]<0)	
				v_h1[i] = 0.0;
		}
		
		//DNN inference stage- output layer/
		for (i=0;i<10;i++){
			results[i] = 0.0;
			for (j=0;j<neuron1;j++){
				results[i] += v_h1[j]*w_o[i][j];
			}
			results[i] += b_o[i];
			if(results[i]<0)	
				results[i] = 0.0;
		}	
		
		//find max value//
		max = results[0];
		max_idx = 0;
		for (i=1;i<10;i++)
			if(max<results[i]){
				max_idx = i;
				max = results[i];
			}
		if (max_idx == ans[t])
			correct++;
		total++;
	}
 
	//accuracy//
	printf("test data count          : %d\n", total);
	printf("accuracy                 : %f%%\n\n",correct/100);
	
	system("pause");
	return 0;
} 


