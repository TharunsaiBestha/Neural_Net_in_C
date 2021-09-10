#include "matrix_double.c"
#include<math.h>
double sigmoid(double n){
    return 1/(1+exp(n));
}
double sigmoid_grad(double n){
    return n*(1.0-n);
}
void log_loss(matrix_f *real,matrix_f *calculated){
    int *temp=(int *)malloc(2*sizeof(int));
    double t=ele(real,*temp,*(temp+1));
    free(temp);
    cmul(real,1.0/t);
    temp=(int *)malloc(2*sizeof(int));
    t=ele(calculated,*temp,*(temp+1));
    free(temp);
    cmul(calculated,1.0/t);
    apply(log,calculated);
    mul_ele(real,calculated);
    cmul(real,-1.0);
    }
void squr_grad(matrix_f *real,matrix_f *calculated){
    sub(real,calculated);
}
void log_grad(matrix_f *real,matrix_f *calculated){
    sub(real,calculated);
}
matrix_f** forward(matrix_f *inputs,matrix_f **weights,int len,double (*fun)(double)){
    matrix_f **temp=(matrix_f **)malloc((len+1)*sizeof(matrix_f *));
    matrix_f *temp_x=inputs;
    matrix_f *temp_inp;
    for(int i=0;i<len;i++){
        *(temp+i)=temp_x;
        temp_inp=temp_x;
        temp_x=mul(*(weights+i),temp_inp);
        apply(fun,temp_x);
    }
    *(temp+len)=temp_x;
    return temp;
}
void backpropagation(matrix_f *real_output,matrix_f **temp,matrix_f **weights,double lr_rate,int len,double (*fun)(double)){
    //matrix_f *temp_real_output;
    matrix_f *temp_x;
    matrix_f *error;
   matrix_f *delta;
    matrix_f *temp_w;
    matrix_f *x;
    error=duplicate(real_output);
    for(int i=len;i>0;i--){
        if(i==len){
        sub(error,*(temp+i));
        delta=duplicate(*(temp+i));
        apply(fun,delta);
        mul_ele(delta,error);
        temp_x=trans(*(temp+i-1));
        temp_w=mul(delta,temp_x);
        destroy(temp_x);
        }
        else{
            x=trans(*(weights+i));
            temp_w=mul(x,delta);
            destroy(delta);
            destroy(x);
            delta=duplicate(*(temp +i));
            apply(sigmoid_grad,delta);
            mul_ele(delta,temp_w);
            destroy(temp_w);
            temp_x=trans(*(temp+i-1));
            //destroy(temp_w);
            temp_w=mul(delta,temp_x);
            destroy(temp_x);
        //display(temp_w);
        }
        cmul(temp_w,lr_rate);
    sub(*(weights+i-1),temp_w);
    destroy(temp_w);}
    //destroy(temp_w);
    //destroy(temp_x);
    destroy(delta);
    destroy(error);
    }
int sat_node(matrix_f *m){
    int c=0;
    for(int i=0;i<m->row;i++){
		for(int j=0;j<m->col;j++){
            if(ele(m,i,j)>0.95 || ele(m,i,j)<0.05)c++;}}
            return c;
}
    void des_temp_out(matrix_f **temp,int len){
          for(int i=1;i<=len;i++){
              destroy(*(temp+i));
          }
        free(temp);
    }



