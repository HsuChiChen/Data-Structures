#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define SIZE 50            

char stack[SIZE];
int top=-1;             // Global declarations
 
push(char elem){        // Function for PUSH operation
    stack[++top]=elem;
    printf("Push %c\n",elem);
}
 
char pop(){            // Function for POP operation/
	printf("Pop %c\n",stack[top]);
    return(stack[top--]);
}
 
 
// Function for precedence  
int pr(char op) { 
    switch(op) { 
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        default:            return 0;
    } 
} 

//InfixToPostfix
char InfixToPostfix(char* infix, char* postfix){                        
    char ch,elem;
    int i=0,k=0;
    push('#');
    while( (ch=infix[i++]) != '\0'){
        if( ch == '(') 
			push(ch);
        else
            if(isalnum(ch)) 
				postfix[k++]=ch; 
            else{
            	postfix[k++]='#'; //Distinguish between two numbers
                if( ch == ')'){
                    while( stack[top] != '(')
                        postfix[k++]=pop();
                    elem=pop(); // Remove (
                }
                else{       // Operator
                    while( pr(stack[top]) >= pr(ch) )
                        postfix[k++]=pop();
                    push(ch);
                }
            }
    }
    while( stack[top] != '#')     // Pop from stack till empty
        postfix[k++]=pop();
    postfix[k]='\0';          // Make postfix as valid string
}

//evaluate postfix
double cal(char op, double p1, double p2) { 
    switch(op) { 
        case '+': return p1 + p2;
        case '-': return p1 - p2; 
        case '*': return p1 * p2; 
        case '/': return p1 / p2; 
    } 
}

double eval(char* postfix) {
    char opand[2] = {'\0'};
    double stack_re[SIZE] = {0.0}; 
	printf("\nPostfix = ");
    printf("%s",postfix);
    printf("    ( # is used to distinguish between two numbers )\n\n");
    printf("Push these number into stack to evaluate postfix\n");
    int top_re, i,k;
    for(top_re = 0, i = 0; postfix[i] != '\0'; i++) {
		switch(postfix[i]) { 
	        case '+': case '-': case '*': case '/':
	            stack_re[top_re - 1] = cal(postfix[i], stack_re[top_re - 1], stack_re[top_re]); 
	            top_re--; 
	            break; 
	        default: 
	        	k = 0;
	        	while(isalnum(postfix[i])){
	        		k++;
	        		i++;
				}
	        	
				if(k==1){
					opand[1] = 0;
					opand[0] = postfix[i-1];
//					printf("1\n");            //test
					printf("%f\n",atof(opand)); //test
					
				}
				else if(k==2){
					opand[0] =  postfix[i-2];
					opand[1] =  postfix[i-1];
//					printf("2\n");                //test
//					printf("%c\n",postfix[i-2]);  //test
//					printf("%c\n",postfix[i-1]);  //test
					printf("%f\n",atof(opand));   //test
				} 
				
				if(postfix[i] != '#')
					i--;
				if(k !=0)
	            	stack_re[++top_re] = atof(opand);
	    } 
    } 
    printf("\n\nResult = ");
    return stack_re[top_re];
}

int main() { 
    char infix[SIZE] = {'\0'}, postfix[SIZE]; 

    //printf("Enter Infix Expression : ");
    //scanf("%s",infix);
    while(scanf("%[^\n]%*c",infix)==1){
    	printf("Input Infix Expression : \n");
    	printf("%s\n",infix);
    	printf("\nHow to convert Infix to postfix:\n");
		InfixToPostfix(infix,postfix);
    	printf("%f", eval(postfix));
    	printf("\n\n\n\n\n\n\n");
	} 
	return 0;
} 
