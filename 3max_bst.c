#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 50
int max_candid[SIZE]; //stack of max node candidate
int top = 0;		  //pointer for stack

int pow_base2(int exponent){ //power of 2
    int base=2,result=1;
    while (exponent != 0){
        result *= base;
        --exponent;
    }
    return result;
}

void build_tree(int *a,int n, int **tree, int start_node, int terminal_node){
	int i, j, max_two;
	//initializion
	for(i=0; i<3; i++){ 
		for(j=0; j<terminal_node; j++){
			tree[i][j] = 0;
		}
	}
	
	//terminal nodes
	for(i = 0; i < n; i++){
		tree[0][start_node+i] = a[i]; //data of terminal nodes
	}
	for(i = 0; i <= start_node; i++){
		tree[1][start_node+i] = i;    //lower of terminal nodes
		tree[2][start_node+i] = i;    //upper of terminal nodes
	}
		
	//other nodes
	for(i = terminal_node-1; i > 0; i = i-2){  //until reach the root of tree
		if(tree[0][i] > tree[0][i-1] )         //max between two number
			max_two = tree[0][i];
		else
			max_two = tree[0][i-1];
		tree[0][(i/2)-1] = max_two;      //data
		tree[1][(i/2)-1] = tree[1][i-1]; //lower
		tree[2][(i/2)-1] = tree[2][i];   //upper
	}
	
	//print tree for test
	printf("\n\n\n");
	printf("The structure of tree:\n");
	for(i=0;i<3;i++){
		for(j=0; j<terminal_node; j++){
			printf("tree[%d][%d] = %d\n",i,j,tree[i][j]);
		}
		printf("\n");
	}
}


void max_candid_f(int lower, int upper, int **tree, int current){ //find max node candidate
	if(lower == tree[1][current] && upper == tree[2][current]){ //hit the range
		max_candid[top++] = tree[0][current];
		printf("lower = %d, upper = %d, current node = %d hit the range\n\n",lower,upper,current);
	}
	else if(upper <= tree[2][2*current+1]){                    //go to left tree
		printf("lower = %d, upper = %d, current node = %d go to left tree\n",lower,upper,current);
		max_candid_f(lower, upper, tree, 2*current+1);
	}
	else if(lower > tree[2][2*current+1]){                     //go to right tree
		printf("lower = %d, upper = %d, current node = %d go to right tree\n",lower,upper,current);
		max_candid_f(lower, upper, tree, 2*current+2);
	}
	else{
		printf("\nsplit to two parts \n");
		printf("first  part: lower = %d, upper = %d, current node = %d \n", lower, tree[2][2*current+1], 2*current+1);
		printf("second part: lower = %d, upper = %d, current node = %d \n\n", tree[2][2*current+1]+1, upper, 2*current+2);
		//change upper and split to left tree
		max_candid_f(lower, tree[2][2*current+1], tree, 2*current+1);
		//change lower and split to right tree
		max_candid_f(tree[2][2*current+1]+1, upper, tree, 2*current+2);
	}
}


int main(){
	srand( time(NULL) ); //time seed
	int n,i,ramdom,lower,upper,max=0;
	printf("type data number:\n");
	scanf("%d", &n);     //read number of data n
	
	//null tree
	if(n == 0){
		printf("NULL Array with no element\n");
		return 0;
	}
	int a[n];            //input array
	for(i = 0; i < n; i++){
		a[i] = (rand()*rand())%100+1; //random number
	}
    
    printf("each element of array generated from time seed :\n");
	for(i = 0 ; i < n ; i++)
		printf("number_array[%d] = %d\n",i,a[i]); //print array[n]
	
	printf("\n\ntype search data array:\n"); 
	scanf("%d %d", &lower,&upper); //read assigned range from lower to upper
	
	//detect overflow of range
	if(lower < 0 || upper >= n){
		printf("the range is beyond the scope\n"); 
		return 0;
	}
	
	//result will straightforwardly be calculated for test
	// for(i = lower; i <= upper; i++)
		// if(max < a[i])
			// max = a[i];
	// printf("result will straightforwardly be calculated when number of array no more than 8 \n");
	// printf("in number_array[%d] ~ number_array[%d], max = %d\n",lower,upper,max);
	
	
	//find th size of tree given array n
	int size_tree = 0;
	while(pow_base2(size_tree) < n){
		size_tree++;
	}
	int node_number = pow_base2(size_tree+1) -1;
	int terminal_node_number = pow_base2(size_tree) -1;
	
	//build a tree with 3-dimension array data structure
	int tree[3][node_number];
	int *p_1[3]={tree[0], tree[1], tree[2]};
	build_tree(a,n,p_1,terminal_node_number,node_number);
	
	//find max node candidate
	printf("Step to find candidate node with the maximum value:\n");	
	int *p_2[3]={tree[0], tree[1], tree[2]};
	int current = 0;
	max_candid_f(lower, upper, p_2, current);
	printf("\n\n\n");
	
	//find max from candidate
	for(i = 0; i < top; i++){
		printf("choosing point %d = %d\n", i+1, max_candid[i]);
		if(max < max_candid[i])
			max = max_candid[i];
	}
	printf("in number_array[%d] ~ number_array[%d], max = %d\n",lower,upper,max);
	return 0;
}
