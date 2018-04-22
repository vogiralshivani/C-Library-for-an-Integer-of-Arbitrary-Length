#include "intal.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

void swap(char *op1, char *op2);
char* pad_zeroes(char* intal,int diff);
int* convert_to_int(char *op);


void* intal_create(const char* str)
{
	
	if(str==NULL)
		return NULL;
	if((str[0]>=65 && str[0]<=90 )|| (str[0]>=97 && str[0]<=122))
		return "NaN";
	int len=strlen(str);
	int i,j;
	for(i=0;i<len;i++)
	{
		if(str[i]!='0')
		{
			j=i;
			break;
		}
	}
	char* intal=(char*)malloc((len-j)*sizeof(char));
	i=0;
	while(j<len)
	{
		if(str[i]>=48 && str[i]<=57)
		{
			intal[i]=str[j];
			j++;
			i++;
		}
		else
		{
			return intal;
		}
	}
	return intal;
}

void intal_destroy(void* intal)
{
	if(intal!=NULL)
		free((char*)(intal));
}

char* intal2str(void* intal)
{
	
	if(intal==NULL)
		return NULL;
	char *a=(char*)intal;
	char *str=(char*)malloc(strlen(a)*sizeof(char));
	strcpy(str,a);
	return str;
}

int intal_compare(void* intal1, void* intal2)
{
	if(intal1==NULL || intal2==NULL) 
		return NULL;

	char *op1=(char*)intal1;
	char *op2=(char*)intal2;


	if(strlen(op1)>strlen(op2))
		return 1;
	else if(strlen(op2)>strlen(op1))
		return -1;
	else

	{
		int i=strcasecmp(op1,op2);

		return i;
	}
	
}

void* intal_add(void* intal1, void* intal2)
{
    char *p1=(char*)intal1;
    char *p2=(char*)intal2;
    char *op1=(char*)malloc((strlen(p1)+1)*sizeof(char));
    char *op2=(char*)malloc((strlen(p2)+1)*sizeof(char));
	strcpy(op1,p1);
	strcpy(op2,p2);
    if(strlen(op1)>strlen(op2))
    {
    	char *temp = (char*)malloc((strlen(op1)+1)*sizeof(char));
        strcpy(temp,op1);
  		strcpy(op1,op2);
  		strcpy(op2,temp);
    }

    int n1=strlen(op1);
    int n2=strlen(op2);
    int diff = n2 - n1;

    int sum,carry = 0;
    int n=(n1>n2)?n1:n2;
    int *result=(int*)malloc((n+1)*sizeof(int));  
    
    int pos=0;
    int i;
    for (i=n1-1; i>=0; i--)
    {
        
        sum =(op1[i]-'0')+(op2[i+diff]-'0')+carry;
        //printf("op1[%d]=%c , op2[%d+%d]=%c ,sum=%d \n",i,op1[i],i,diff,op2[i+diff],sum);
        result[i+diff]= (sum%10);
    
        carry = sum/10;
        pos++;

    }

    for (i=n2-n1-1; i>=0; i--)
    {
        sum = ((op2[i]-'0')+carry);
        result[i]=(sum%10);
        carry = sum/10;
        pos++;
    }
    char *ans=(char*)malloc((n+1)*sizeof(char));
    get_me_a_string(result,n+1,ans,n+1);
   
    if (carry)
    {
    
    	strrev(ans);
    	strcat(ans,"1");
    
    	strrev(ans);
    }



   
    
    return ans;
}


void* intal_diff(void* intal1, void* intal2)
{
	char *a=(char*)intal1;
	char *b=(char*)intal2;

	if(intal_compare(a,b)==0)
		return "0";
	if(a[0]=='0' && strlen(a)==1)
		return b;
	if(b[0]=='0' && strlen(b)==1)
		return a;

	if(intal_compare(a,b)<0)
		return intal_diff(b,a);

	char *op1=(char*)malloc(sizeof(char));
	char *op2=(char*)malloc(sizeof(char));

	op1=a;
	op2=b;


	int i;
	int check=intal_compare(op1,op2);
	if(check<0)
	{
		char *temp = (char*)malloc((strlen(op1)+1)*sizeof(char));
        strcpy(temp,op1);
  		strcpy(op1,op2);
  		strcpy(op2,temp);
	}

	
	int n1=strlen(op1);
	int n2=strlen(op2);
	
	//reversal of strings
	
	
	strrev(op1);
	strrev(op2);
	
	int sub,carry=0;
	int *diff=(int*)malloc((n1)*sizeof(int));


	for(i=0;i<n2;i++)
	{

		sub = (op1[i]-'0')-(op2[i]-'0')-carry;
		//printf("op1[%d]=%c , op2[%d]=%c ,sub=%d \n",i,op1[i],i,op2[i],sub);
		if (sub < 0)
		{
			sub = sub + 10;
			carry = 1;
		}
		else
			carry = 0;

		diff[i]=sub;
		
	}
	for (i=n2; i<n1; i++)
	{
		sub = ((op1[i]-'0') - carry);
		if (sub < 0)
		{
			sub = sub + 10;
			carry = 1;
		}
		else
			carry = 0;
			
		diff[i]=sub;
		
	}

	char *answer=(char*)malloc((n1)*sizeof(char));
	get_me_a_string(diff,n1+1,answer,n1+1);
	strrev(answer);
	answer = (char*)intal_create(answer);
	strrev(op1);
	strrev(op2);
	return answer;
}

void get_me_a_string(int * int_array, int array_size, char * output_string, int output_string_max_size)
{
    if(!int_array || !output_string)
        return;

    char * aux_string = NULL;

    //Depending on the compiler int is 2-byte or 4 byte.
    //Meaning INT_MAX will be at most 2147483647 (10 characters + 1 '\0').
    aux_string = (char *) malloc(11);
    if(!aux_string)
        return;

    int i;
    int current_array_size = 0;
    for(i = 0; i < array_size; i++)
    {
        sprintf(aux_string, "%d", int_array[i]);
        current_array_size += strlen(aux_string);
        if(current_array_size < output_string_max_size)
            strcat(output_string, aux_string);
        else
            break;
    }

    free(aux_string);
}

void* intal_increment(void* intal)
{
	if(intal==NULL)
		return NULL;

	if(strcmp(intal,"NaN")==0)
		return "0";
	char *op1=(char*)intal;
	char *op2=(char*)intal_create("1");
	char *result=(char*)malloc(sizeof(char));
	result=(char*)intal_add(op1,op2);

	return result;
}
void strrev(char *a)
{
    int x=strlen(a);
    char *b=(char*)malloc(x*sizeof(char));
    int i;
    int k=x-1;
    for(i=0;i<x;i++)
    {
        b[i]=a[k];
        k--;
    }
    for(i=0;i<x;i++)
        {
            a[i]=b[i];
        }
        

}
void* intal_decrement(void* intal)
{
	if(intal==NULL)
		return NULL;


	char *op1=(char*)intal;

	if(strcmp(intal,"NaN")==0)
		return "0";
	char *op2=(char*)intal_create("1");
	char *result=(char*)malloc(sizeof(char));
	result=(char*)intal_diff(op1,op2);

	return result;
}
	
void* intal_multiply(void* intal1, void* intal2)
{
    char *p1=(char*)intal1;
    char *p2=(char*)intal2;
    if((p1[0]=='0' && strlen(p1)==1) || (p2[0]=='0' && strlen(p2)==1))
    	return "0";
    if(p1[0]=='1' && strlen(p1)==1)
    	return p2;
    if(p2[0]=='1' && strlen(p2)==1)
    	return p1;

    char *p=(char*)malloc(sizeof(char));
    char *a=p1;
    char *b=p2;
    int n1=strlen(a);
    int n2=strlen(b);
    int n=n1+n2;

    if(n1==0 || n2==0)
    {
        p[0]='0';
        return p;
    }
    
    int *result=(int*)malloc((n+1)*sizeof(int));
    int i_n1=0;
    int i_n2=0;
    int i,j;
    for(i=0;i<(n1+n2);i++)
        result[i]=0;
        
    for(i=n1-1;i>=0;i--)
    {
        int carry=0;
        int num1=a[i]-'0';
        i_n2=0;
        for(j=n2-1;j>=0;j--)
        {
            int num2=b[j]-'0';
       
            int sum=num1*num2+result[i_n1+i_n2]+carry;
    
            carry=sum/10;
            result[i_n1+i_n2]=sum%10;
          
            i_n2++;
        }
        if(carry>0)
            result[i_n1+i_n2]+=carry;
        i_n1++;


    }

    char *s=(char*)malloc((n+1)*sizeof(char));
    get_me_a_string(result,n+1,s,n+1);
 	strrev(s);
 	char *res=(char*)intal_create(s);

 	return res;
}


void* intal_divide(void* intal1, void* intal2)
{
	if(intal1==NULL || intal2==NULL) 
		return NULL;


	char *a=(char*)intal1;
	char *b=(char*)intal2;
	
	int m=0;

	if(strlen(b)==1 && b[0]=='0')
	{
		return "NaN";
	}

	if(intal_compare(a,b)<0)
	{
		return "0";
	}

	if(intal_compare(a,b)==0)
	{
		return "1";
	}

	if(b[0]=='1' && strlen(b)==1)
	{
		return a;
	}
	
	int count=0;
	int n2=strlen(b)-1;
	int n1=strlen(a)-1;
	char *op1=(char*)malloc(n1*sizeof(char));
	char *op2=(char*)malloc(n2*sizeof(char));
	strcpy(op1,a);
	strcpy(op2,b);
	int len2=n2;
	int flag=1;
	if(n1==n2)
	{
		
		while(intal_compare(op1,op2)!=-1)
		{
			op1=(char*)intal_diff(op1,op2);
			count+=1;
		}
		char *s=(char *)malloc(len2);
		sprintf(s,"%d",count);
		s=realloc(s,strlen(s));
		return s;
	}
	char *q=(char*)malloc(sizeof(char)*strlen(op1));
	if(n1!=n2)
	{
	 	int i=0; 
		int j=len2-1;
		char *dividend=(char*)malloc((len2+1)*sizeof(char));
		strncpy(dividend,op1,len2);
		int k=len2;
		if(intal_compare(dividend,op2)<0)
		{
			if(strlen(op1)>len2)
			{
				strncat(dividend,&op1[len2],1);
				j++;
				k++;
			}
		}
		char *quotient=dividend;
		//count=0;
		flag=1;
		while(flag)
		{
			count=0;
			j++;
			while(intal_compare(quotient,op2)>0)
			{
				count+=1;
				quotient=intal_diff(quotient,op2);
				flag=1;
			}
			sprintf(dividend,"%d",count);
			strcat(q,dividend);
			if(j>=strlen(op1))
			{
				flag=0;
			}
			else
			{
				flag=1;
				char *divi=(char*)malloc(sizeof(char));
				divi=quotient;
				char *divi2=(char *)malloc((strlen(divi)+1)*sizeof(char));
				strcat(divi2,divi);
				strncat(divi2,&op1[j],1);
				quotient=divi2;
				flag=1;
			}
		}
	}
	char *res=(char*)intal_create(q);
 	return res;
}


/*int* convert_to_int(char *op)
{
	int n=strlen(op);
	int i;
	int *int_array=(int*)malloc(n*sizeof(int));
	for(i=0;i<n;i++)
	{
		int_array[i]=op[i]-48;
	}

	for(i=0;i<n;i++)
		printf("%d",int_array[i]);
	printf("\n");
	return int_array;
}*/

static void* pow_2(void *intal)
{
    return intal_multiply(intal,intal);
}
void* intal_pow(void* intal1, void* intal2)
{
	
	if(intal1==NULL || intal2==NULL) 
		return NULL;

	char *a=(char*)intal1;
	char *b=(char*)intal2;




	if(a[0]=='0' && strlen(a)==1) 
		return "0";

	if((a[0]=='1' && strlen(a)==1) || (b[0]=='0' && strlen(b)==1)) 
		return "1";
	
	if(b[0]=='0' && strlen(b)==1) 
		return "1";

	if(b[0]=='1' && strlen(b)==1)
		return a;


    int flag=1;
    if((b[strlen(b)-1]-'0')%2==0)
    {
        flag=0;//n%2==0
    }
    char *rem=(char*)malloc(2*sizeof(char));
    if(flag==1)
    {
    	rem[0]=flag+48;
    	rem[1]='\0';
    }
    if(flag==0)
    {
    	rem[0]=flag+48;
    	rem[1]='\0';
    }
   	char *t=(char*)intal_create("2");
	return intal_multiply(pow_2(intal_pow(a,intal_divide(b,t))),intal_pow(a,rem));
}
	

	




