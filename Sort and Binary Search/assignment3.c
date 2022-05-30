    
                                    /* Data Structure and Algorithm: Merge Sort/Insertion Sort and Binary Search 
                                                       This program is written by: Omar Cisse */ 
    
    
    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>


    #define NEAR -1
    #define NOT_NEAR 1
    #define SAME 0

    typedef struct Coordinates{
        int X;
        int Y;
        

    }Coordinates;

    int compareTo(Coordinates *ptrPt1, Coordinates *ptrPt2);
    void InsertionSort(Coordinates **list, int n);
    void SortFuction(Coordinates **list, int size, int t);
    Coordinates **ReadData(FILE *fp,int *size);
    int BinarySearch(Coordinates** list,int l,int r, Coordinates *lookOut);
    void WatchForTarget(Coordinates **list_all, Coordinates **target, int n,int s,FILE*output);
    void MergeSort(Coordinates **list,int l, int r);
    void Merge(Coordinates**list,int l, int m,int r);
    void display(Coordinates** list, int*size,FILE*output);
  


    Coordinates *my_location;

    int BinarySearch(Coordinates** list,int l,int r, Coordinates *lookOut){
        while( r >= l){
            int m = l+(r-l)/2;
        int check = compareTo(list[m],lookOut);
        if(check == SAME){
            return m;
        }
        else if(check == NOT_NEAR){
            return BinarySearch(list,l,m-1,lookOut);
        } else  {
            return BinarySearch(list,m+1,r,lookOut);
        }
        }
        return -1;
    }
    void WatchForTarget(Coordinates **list_all, Coordinates **target, int n,int s,FILE*output){
    for( int i=0;i<s;i++){
        Coordinates *temp = (Coordinates*)malloc(sizeof(Coordinates));
        temp = target[i];
        int objective_met = BinarySearch(list_all,0,n-1,temp);
        
        if(objective_met == -1){
            fprintf(output,"%d %d not found\n", temp->X, temp->Y);
        } else {
            fprintf(output,"%d %d found at rank %d\n", list_all[objective_met]->X, list_all[objective_met]->Y, objective_met+1);
        }
        
    }
    }



    void InsertionSort(Coordinates **list, int n){
        
        for(int i=1;i<n;i++){
            Coordinates *temp = (Coordinates*)malloc(sizeof(Coordinates));
            temp = list[i];
            int j= i-1;
            while(j>=0){
            int cp = compareTo(list[j],temp);
            if(cp == NOT_NEAR){
                list[j+1] = list[j];
            } else if(cp == NEAR || cp == SAME){
                break;
            } 
            j--;
            }
            list[j+1] = temp;
            
        }
        printf("The list below is sorted: \n");
        for(int i =0;i< n;i++){
            printf(" %d  %d \n", list[i]->X, list[i]->Y);
        }
        
    }
    void Merge(Coordinates**list,int l, int m,int r){
        int i, j, k;
        int n1 = m - l + 1;
        int n2 =  r - m;

        Coordinates **L = (Coordinates**)malloc(n1*sizeof(Coordinates*));
        Coordinates **R = (Coordinates**)malloc(n2*sizeof(Coordinates*));

        for (i = 0; i < n1; i++){
            L[i] = list[l + i];
        } 
        for (j = 0; j < n2; j++){
            R[j] = list[m + 1+ j];
        }

        i = 0; 
        j = 0; 
        k = l; 

        while (i < n1 && j < n2)
        {
            int catch = compareTo(L[i],R[j]);
            if (catch == NEAR)
            {
                list[k] = L[i];
                i++;
            }
            else
            {
                list[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1)
        {
            list[k] = L[i];
            i++;
            k++;
        }
        while (j < n2)
        {
            list[k] = R[j];
            j++;
            k++;
        }
        free(L);
        free(R);
            
    }
    void MergeSort(Coordinates **list,int l, int r){
        if(l < r){
            int m = (l+r)/2;
            MergeSort(list,l,m);
            MergeSort(list,m+1,r);

            Merge(list,l,m,r);
        }

    }

    void SortFunction(Coordinates **list, int size, int t){
        if(size <= t){
        InsertionSort(list,size);
        } else {
            MergeSort(list,0,size-1);
            return;
        }

    }

    int compareTo(Coordinates *ptrPt1, Coordinates *ptrPt2){
        
    //printf("n");
    double x1,x2,y1,y2;
    double d1,d2;
    x1 = (ptrPt1->X - my_location->X) * (ptrPt1->X - my_location->X);
    x2 = (ptrPt2->X - my_location->X) * (ptrPt2->X - my_location->X);
    y1 = (ptrPt1->Y - my_location->Y) * (ptrPt1->Y - my_location->Y);
    y2 = (ptrPt2->Y - my_location->Y) * (ptrPt2->Y - my_location->Y);
    
    d1 = sqrt(x1+y1);
    d2 = sqrt(x2+y2);

    // printf("The distance for first pointer is %.2lf and the distance for second pointer is %.2lf\n",d1,d2);
    if(d1 < d2){
        //printf("It is near\n");
        return -1;
    } else if(d1 == d2){
            if(ptrPt1->X < ptrPt2->X){
                //printf("The first pointer wins\n");
                return -1;
            } else if(ptrPt1->X > ptrPt2->X){
                //printf("The second pointer wins\n");
                return 1;
            } else if(ptrPt1->X == ptrPt2->X){
                if(ptrPt1->Y < ptrPt2->Y){
                    return -1;
                } else if(ptrPt1->Y > ptrPt2->Y) {
                    return 1;
                } else if (ptrPt1->X == ptrPt2->X && ptrPt1->Y == ptrPt2->Y){
                //printf("They are the same\n");
                return 0;
            }
            } 
        }  else if(d1 > d2){
            //printf("The second pointer wins");
            return 1;
        }  
    
    

    
    
    
    }

    Coordinates **ReadData(FILE *fp,int *size){
        Coordinates **temp = (Coordinates**)malloc(*size*sizeof(Coordinates*));
        int x,y,i;
        for( i=0;i<*size;i++){
            temp[i] = (Coordinates*)malloc(sizeof(Coordinates));
            fscanf(fp,"%d %d", &x,&y);
            temp[i]->X = x;
            temp[i]->Y = y;
        }
        temp[*size] = NULL;
        return temp;
    }

    void display(Coordinates** list, int*size, FILE *output){
        int i;
        for(int i=0;i<*size;i++){
            fprintf(output," %d  %d\n", list[i]->X, list[i]->Y);
        }
    }

  


    int main(){
        FILE *input = NULL;
        FILE *output = NULL;
        int x,y,n,s,t;
        Coordinates **list_allLocation = NULL;
        Coordinates **target = NULL;
        input = fopen("assignment3input.txt", "r");
        if(input == NULL){
            printf("File not found\n");
            exit(-1);
        }
        fscanf(input,"%d %d %d %d %d", &x,&y,&n,&s,&t);
        my_location = (Coordinates*)malloc(sizeof(Coordinates));
        my_location->X = x;
        my_location->Y = y;
        //printf("My location is : %d %d\n", my_location->X, my_location->Y);
        list_allLocation = ReadData(input,&n);
        target = ReadData(input,&s);
        fclose(input);
        SortFunction(list_allLocation,n,t);
        output = fopen("out.txt","w");
        if(output == NULL){
            printf("Failed to open file\n");
            exit(-1);
        }
        display(list_allLocation,&n,output);
        WatchForTarget(list_allLocation,target,n,s,output);
        fclose(output);
        return 0;
    }