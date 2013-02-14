#include<stdio.h>

int power(int a,int b);
struct trans
{
  char alpha;
	int val;
	short int count;
	short int next;
};

struct trans p1;
int size=0;

struct get
{
	char alpha;
	int val;
	int count;
	struct get *next;
};

struct get *h1,*h2;

struct compress
{
	int val;
	struct compress *next;
};

struct read
{
	int val;
};
struct read t,t1;

struct compress *c1,*c2,*rec1;

main()
{
	FILE *fp;
	int extra=0;
	h1=NULL;
	h2=NULL;
	c1=NULL;
	c2=NULL;
	rec1=NULL;

	fp=fopen("bfile","rb");
	printf("%u\n",extra=getw(fp));

	while(fread(&p1,sizeof(struct trans),1,fp)!=NULL)
	{
		printf("%d\t%d\t%c\n",p1.val,p1.count,p1.alpha);
		struct get *new=(struct get *)malloc(sizeof(struct get));
		new->alpha=p1.alpha;
		new->val=p1.val;
		new->count=p1.count;
		
		if(h1==NULL)
		{
			h1=new;
			h2=new;
		}
		else
		{
			h2->next=new;
			h2=new;
		}
		
		if(p1.next==0)
		break;
	}

	/*h2=h1;
	while(h2!=NULL)
	{
		printf("%c\t",h2->alpha);
		h2=h2->next;
	}*/

	unsigned int ch,i;
	/*while((ch=getw(fp))!=-1)
	{
		printf("%u\t",ch);
	}*/

	printf("\n");

	while(fread(&t,sizeof(struct read),1,fp)!=NULL)
	{	
	printf("%u\t",t.val);

	
	
	ch=t.val;
		for(i=0;i<32;i++)
		{
			struct compress *new=(struct compress *)malloc(sizeof(struct compress));
			new->next=NULL;
			if((ch & power(2,i)) == power(2,i))
			{
				new->val=1;
				if(c1==NULL)
				{
				c1=new;
				rec1=new;
				}
				else
				{
					rec1->next=new;
					rec1=new;
				}
				//printf("%d",1);
			}
			else
			{
				new->val=0;
				if(c1==NULL)
				{
				c1=new;
				rec1=new;
				}
				else
				{
					rec1->next=new;
					rec1=new;
				}
		
				//printf("%d",0);
			}
		}	
	
	}

	fclose(fp);


	c2=c1;
	printf("\n");
	unsigned long int j=0;
	while(c2!=NULL)
	{
		//printf("%d",c2->val);
		c2=c2->next;
		j++;
		
	}
	
	printf("%u\n",j);
	unsigned long int arr[j],size=0,sum=0,count=0;
	fp=fopen("decompress","w");

	struct compress *c3;

	c2=c1;
	
	
	c2=c1;
	while(c2!=NULL)
	{
		arr[size++]=c2->val;
		c2=c2->next;
	}
	if(extra>0)
	size=size-32+extra;

	j=0;
	for(i=0;i<=size;i++)
	{
		sum=sum+arr[i]*power(2,j++);
		count++;
	
		h2=h1;
		while(h2!=NULL)
		{
			if(h2->val==sum && h2->count==count)
			{
				sum=0;count=0;j=0;
				
				fputc(h2->alpha,fp);
				break;
			}
			h2=h2->next;
		}	
	}
	
}


int power(int a,int b)
{
	int sum=0;
	if(b==0)	
	return 1;
	else if(b==1)
	return a;
	else
	{
		int i;
		
		for(i=1;i<=b-1;i++)
		{
			if(sum==0)
			sum=4;
			else
			sum=sum*2;
		}
	}
	return sum;
}
