#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
void my_init(int n) {
    srand(n);
}

// double get_random(double f) {
//     return (rand() % 16);
// }
double get_random(double f) {
    return rand()/(RAND_MAX*f);
}
struct mat{
	int row;
	int col;
	double *data;};
struct mat* creat(int a,int b){
	struct mat* temp=(struct mat *)malloc(sizeof(struct mat));
	temp->row=a;
	temp->col=b;
	temp->data=(double *)malloc(a*b*sizeof(double));
	for(int i=0;i<temp->row;i++){
                for(int j=0;j<temp->col;j++){
                        *(temp->data+temp->col*i+j)=0;
	return temp;}}}
struct mat* creat_i(int a){
	struct mat* temp=creat(a,a);
	for(int i=0;i<a;i++){
		*(temp->data+temp->col*i+i)=1.0;
	}
	return temp;
}
double ele(struct mat *m,int row,int col){
	return *(m->data+m->col*row+col);
}
void fill(struct mat *m,double x){
	for(int i=0;i<m->row;i++){
		for(int j=0;j<m->col;j++){
			*(m->data+m->col*i+j)=x;}}}
void fill_ele(struct mat *m,int row,int col,double val){
    *(m->data+m->col*row+col)=val;
}
void fill_random_i(struct mat *m){
	for(int i=0;i<m->row;i++){
       // my_init(i);
		for(int j=0;j<m->col;j++){
			*(m->data+m->col*i+j)=(double)(rand()%5);}}}
void fill_random(struct mat *m,double f){
	for(int i=0;i<m->row;i++){
       // my_init(i);
		for(int j=0;j<m->col;j++){
			*(m->data+m->col*i+j)=(get_random(f)*f);}}}
void display(struct mat *m){
        for(int i=0;i<m->row;i++){
                for(int j=0;j<m->col;j++){
                        printf("%f ",*(m->data+m->col*i+j));}
					printf("\n");}
					printf("\n");}
struct mat* add(struct mat *a,struct mat *b){
	if((a->col==b->col) && (a->row==b->row)){
		for(int i=0;i<a->row;i++){
		for(int j=0;j<a->col;j++){
			*(a->data+a->col*i+j)=*(a->data+a->col*i+j)+*(b->data+b->col*i+j);}}
			return a;
	}
	else{
		printf("Matrix miss matches\n");
		return NULL;
	}
}
struct mat* sub(struct mat *a,struct mat *b){
	if((a->col==b->col) && (a->row==b->row)){
		for(int i=0;i<a->row;i++){
		for(int j=0;j<a->col;j++){
			*(a->data+a->col*i+j)=*(a->data+a->col*i+j)-*(b->data+b->col*i+j);}}
			return a;
	}
	else{
		printf("Matrix miss matches\n");
		return NULL;
	}
} 
struct mat* mul(struct mat *a,struct mat *b){
	struct mat *temp;
	if(a->col==b->row){
		temp=creat(a->row,b->col);
		for(int i=0;i<a->row;i++){
			for(int j=0;j<b->col;j++){
				for(int k=0;k<a->col;k++){
					*(temp->data +temp->col*i+j)=*(temp->data +temp->col*i+j)+ele(a,i,k)*ele(b,k,j);
				}
			}
		}
	return temp;}
	else{
		printf("Miss Match of matrices\n");
	return NULL;}
}
void cmul(struct mat *a,double val){
	for(int i=0;i<a->row;i++){
		for(int j=0;j<a->col;j++){
			*(a->data+a->col*i+j)=val*ele(a,i,j);}}
}
void row_mul(struct mat *m,int row,int val){
	int t;
	for(int i=0;i<m->col;i++){
		t=*(m->data+m->col*row+i);
		t=val*t;
		*(m->data+m->col*row+i)=t;
	}
}
void row_sub(struct mat *m,int row1,int row2){
	int t1,t2;
	for(int i=0;i<m->col;i++){
		*(m->data+m->col*row1+i)=*(m->data+m->col*row1+i)-*(m->data+m->col*row2+i);
	}
}
void det_arrange(struct mat *m,int p,double *c){
	int t,t1;
	for(int i=p+1;i<m->row;i++){
		t1=ele(m,i,p);
		t=ele(m,p,p);
        if(t1!=0){
		row_mul(m,i,t);
		row_mul(m,p,t1);
		row_sub(m,i,p);
        *c=(*c)*t1*t;}
        printf("%d %d\n",t,t1);
	}
	//display(m);
}
void row_swap(struct mat *m,int row1,int row2){
	int temp1,temp2;
	for(int i=0;i<m->col;i++){
		temp1=ele(m,row1,i);
		temp2=ele(m,row2,i);
		*(m->data+m->col*row1+i)=temp2;
		*(m->data+m->col*row2+i)=temp1;
	}
}
double det(struct mat *m){
    double temp=1;
    double *c=(double *)malloc(sizeof(double));
    *c=1;
	for(int i=0;i<m->col;i++){
		if(ele(m,i,i))det_arrange(m,i,c);
		else{
			for(int j=i;j<m->row;j++){
				if(ele(m,j,i)){row_swap(m,i,j);det_arrange(m,i,c);break;}
			}
		}
	}
    for(int i=0;i<m->col;i++){
		temp=temp*ele(m,i,i);
	}
    printf("%f %f\n",temp,*c);
	return temp/(*c);
}
struct mat* trans(struct mat *a){
struct mat *temp;
temp=creat(a->col,a->row);
for(int i=0;i<temp->row;i++){
		for(int j=0;j<temp->col;j++){
			*(temp->data+temp->col*i+j)=ele(a,j,i);}}
return temp;
}
void cmat_add(struct mat *a,double val){
    for(int i=0;i<a->row;i++){
		for(int j=0;j<a->col;j++){
 *(a->data+a->col*i+j)=*(a->data+a->col*i+j)+val;   
}}}
void destroy(struct mat *m){
    free(m->data);
    free(m);
}
void row_div(struct mat *m,int row,double val){
	double t;
for(int i=0;i<m->col;i++){
		t=*(m->data+m->col*row+i);
		t=t/val;
		*(m->data+m->col*row+i)=t;
	}
}
void norm_mat(struct mat * m,struct mat* temp){
for(int i=0;i<m->row;i++){
	row_div(temp,i,ele(m,i,i));
	row_div(m,i,ele(m,i,i));
}
}
void inv_arrange(struct mat* m,struct mat* temp,int p){
double t,t1;
for(int i=0;i<m->row;i++){
	if(i!=p){
	t1=ele(m,i,p);
		t=ele(m,p,p);
        if(t1!=0){
		row_mul(m,i,t);
		row_mul(m,p,t1);
		row_sub(m,i,p);
		row_mul(temp,i,t);
		row_mul(temp,p,t1);
		row_sub(temp,i,p);		
	}
}
}}
struct mat* inv(struct mat* m){
struct mat* temp=creat_i(m->row);
for(int i=0;i<m->row;i++){
	inv_arrange(m,temp,i);
}
norm_mat(m,temp);
return temp;
}
void apply(double (*fun)(double),struct mat* a){
	for(int i=0;i<a->row;i++){
		for(int j=0;j<a->col;j++){
			*(a->data+a->col*i+j)=fun(ele(a,i,j));	
}}}
struct mat* duplicate(struct mat* a){
	struct mat* dup=creat(a->row,a->col);
	for(int i=0;i<a->row;i++){
		for(int j=0;j<a->col;j++){
			*(dup->data+dup->col*i+j)=ele(a,i,j);
}}
return dup;}
void mul_ele(struct mat *m,struct mat *n){
	if(m->col==n->col && m->row==n->row){
	for(int i=0;i<m->row;i++){
		for(int j=0;j<m->col;j++){
			*(m->data+m->col*i+j)=ele(m,i,j)*ele(n,i,j);
}}}}
void div_ele(struct mat *m,struct mat *n){
	if(m->col==n->col && m->row==n->row){
	for(int i=0;i<m->row;i++){
		for(int j=0;j<m->col;j++){
			*(m->data+m->col*i+j)=ele(m,i,j)/ele(n,i,j);
}}}}
void add_ele(struct mat *m,double val){
	for(int i=0;i<m->row;i++){
		for(int j=0;j<m->col;j++){
			*(m->data+m->col*i+j)=ele(m,i,j)+val;
}}
}
struct mat* diagnol(struct mat *m){
	struct mat* temp;
	if(m->col==1){
		temp=creat(m->row,m->row);
		for(int i=0;i<m->row;i++){
			*(temp->data+temp->col*i+i)=ele(m,i,0);
	}}
	else{
		temp=creat(m->col,m->col);
		for(int i=0;i<m->col;i++){
			*(temp->data+temp->col*i+i)=ele(m,0,i);
	}}
	return temp;
}
struct mat* creat_p(int row,int col,int len,double *d){
	double *p=d;
	int i=0;
	struct mat *m=creat(row,col);
	for(int i=0;i<m->row;i++){
		for(int j=0;j<m->col;j++){
			*(m->data+m->col*i+j)=*(p+i);
			i++;
}}
return m;
}
int* max(struct mat *m){
	double max=-1000;
	int *res=(int *)malloc(2*sizeof(int));
	for(int i=0;i<m->row;i++){
		for(int j=0;j<m->col;j++){
			if(max<ele(m,i,j)){max=ele(m,i,j);*res=i;*(res+1)=j;}}}
return res;
}

typedef struct mat matrix_f;
// int main(){
// 	matrix_f *a;
// 	matrix_f *t;
// 	a=creat_i(3);
// 	fill_random_i(a);
// 	display(a);
// 	t=inv(a);
// 	display(t);
// 	t=mul(a,t);
// 	display(t);
// 	display(a);
// }
