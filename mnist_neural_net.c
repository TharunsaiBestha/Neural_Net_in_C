#include "neural_network.c"
#include "mnist_to_matrix.c"
int main(){
    //int *data_i=init_i(790);
    int count=0;
    int *r;
    matrix_f *X;
    matrix_f **temp;
    float init_f=0.01;
    //double *temp_f=init_d(784);
    double *temp_f;
    int iter=10;
    matrix_f *Y=creat(10,1);
    matrix_f *W[]={creat(100,784),creat(10,100)};
    //X=creat_p(784,1,784,image_input(0,0,'r'));
    //fill_ele(Y,0,0,1.0);
    fill_random(*(W),0.1);
    fill_random(*(W+1),0.1);
    cmul(*(W+1),init_f);
    cmul(*(W),init_f);
    //display(Y);
    //r=max(Y);
    //printf("%d %d",*r,*(r+1));
    //cmul(X,init_f);
    for(int i=0;i<iter;i++){
        count=0;
        for(int j=0;j<3000;j++){
            for(int k=0;k<10;k++){
                //image_input(rand()%10,j,'r',temp_f,data_i);
               temp_f= image_input(k,j,'r');
                //printf("%d",rand()%10);
                X=creat_p(784,1,784,temp_f);
               free(temp_f);
                temp_f=NULL;
                cmul(X,init_f);
                fill_ele(Y,k,0,1.0);
                //cmul(Y,init_f);
     temp=forward(X,W,2,sigmoid);
     backpropagation(Y,temp,W,0.1,2,sigmoid_grad);
   //  display(*(temp));
     des_temp_out(temp,2);
     destroy(X);
     //free(temp_f);
     fill_ele(Y,k,0,0.0);}
     if(j%1000==0){
    printf("iteration: %d \n",(++count)*1000);
     printf("ITERATION NUMBER:%d\n",i);
    // printf("Out of loop\n");
     for(int i=0;i<10;i++){
         //image_input(i,100,'r',temp_f,data_i);
         temp_f= image_input(i,100,'r');
      X=creat_p(784,1,784,temp_f);
      free(temp_f);
       cmul(X,init_f);
     temp=forward(X,W,2,sigmoid);
     //display(*(temp+1));
     //display(*(temp+2));
     r=max(*(temp+2));
     des_temp_out(temp,2);
  //   printf("%d %d\n",*r,*(r+1));
     destroy(X);
     free(r);
}
//printf("First layer sturated node : %d\n",sat_node(*(temp+1)));
//printf("Second layer sturated node : %d\n",sat_node(*(temp+2)));
}}}
}
