
                                                    /* Data Structure and Algorithm : Queue Implementation Using Linked List
                                                         This program is written by: Omar Cisse */ 
    
    
    #include <stdio.h>
    #include <stdlib.h>
    #include <malloc.h>
    #include <string.h>

        #define MAX_NAME 10
        #define SIZE 12
        


    typedef struct Customers{
            char *name;
            int number_items;
            int timeT;
            int line_number;
        }Customers;

        typedef struct Node {
            Customers *data;
            struct Node *next;
        }Node;

        typedef struct Queue{
            Node *front;
            Node *rear;
        }Queue;

        Queue* init();
        void Dequeue(Queue *qq);

        int isEmpty(Queue *q){
            if(q->front == NULL && q->rear == NULL){
                return 1;
            } else{
                return 0;
            }
        }
        
        Customers* peek(Queue *qq){
        return qq->front->data;
        }
        void process(Queue** qq, int *n, FILE*op){
            
            int it = 0;
            Customers *custumer_AtCheckout = (Customers*)malloc(sizeof(Customers));
            custumer_AtCheckout = peek(qq[it]);
            int time_acc = 30 + 5 * (custumer_AtCheckout->number_items) + custumer_AtCheckout->timeT;
            fprintf(op,"%s from line %d checks out at time %d\n", custumer_AtCheckout->name, custumer_AtCheckout->line_number, time_acc);
            int starting_time = time_acc;
            Dequeue(qq[it]);
            while(it != SIZE){
                int count = 0;
                for(int i=0;i<SIZE;i++){
                    int a = isEmpty(qq[i]);
                    if(a == 1){
                        count++;
                    }
                }
                if(count == SIZE){
                    return;
                }

                
                int a = isEmpty(qq[it]);
                if(a != 1){
                    int check = 0;
                Customers* temp = (Customers*)malloc(sizeof(Customers));
                temp = peek(qq[it]);
                for(int i=it+1;i<SIZE;i++){
                    int a = isEmpty(qq[i]);
                    if(a != 1){
                        Customers* tp = (Customers*)malloc(sizeof(Customers));
                        tp = peek(qq[i]);
                        if(tp->number_items < temp->number_items){
            
                                check++;
                                break;
                            }
                        }
                    }
                
                if(check == 0){
                    if(temp->timeT > starting_time){
                        int tt = temp->number_items *5 + 30 + temp->timeT;
                        fprintf(op,"%s from line %d checks out at time %d\n", temp->name, temp->line_number, tt);
                    } else {
                    time_acc += temp->number_items *5 + 30;
                fprintf(op,"%s from line %d checks out at time %d\n", temp->name, temp->line_number, time_acc);
                    }
                
                if(qq[it]->front->next != NULL && it > 0 || it >0){
                    Dequeue(qq[it]);
                    it = 0;
                } else{
                    Dequeue(qq[it]);
                    it++;
                }
                } else if(it == SIZE-1) {
                it = 0;
                }  else {
                    it++;
                } 
                } else{
                    it++;
                }    
            
            }    
        }
    Node* newNode(FILE *fp, int* t, int *m)
    {
        Node* temp = (Node*)malloc(sizeof( Node));
        temp->data = (Customers*)malloc(sizeof(Customers));
        char name[MAX_NAME];int x;
        fscanf(fp,"%s %d", name, &x);
        int l = strlen(name) + 1;
        temp->data->name = (char*)malloc(l*sizeof(char));
        strcpy(temp->data->name, name);
        temp->data->timeT = *t;
        temp->data->line_number = *m;
        temp->data->number_items = x;
        temp->next = NULL;
        return temp;
    }

    Queue* init()
    {
        Queue* q = ( Queue*)malloc(sizeof( Queue));
        q->front = q->rear = NULL;
        return q;
    }


    void Enqueue(FILE *fp, Queue* q, int *t, int *m)
    {

        Node* temp = newNode(fp,t,m);

        if (q->rear == NULL) {
            q->front = q->rear = temp;
            return;
        }

        q->rear->next = temp;
        q->rear = temp;
    }


    void Dequeue( Queue* q)
    {

        if (q->front == NULL)
            return;

        
        Node* temp = q->front;

        q->front = q->front->next;


        if (q->front == NULL)
            q->rear = NULL;
        free(temp->data->name);
        free(temp->data);
        free(temp);
    }


    int main()
    {
    FILE* fp = fopen("assignment2input.txt","r");
            FILE* op = NULL;
            int c;
            
            if(fp==NULL){
                exit(-1);
            }

            op = fopen("out.txt", "w");
            if(op == NULL){
                exit(-1);
            }
            fscanf(fp,"%d", &c);
            
            for(int i= 0; i<c;i++){
            Queue **qq = (Queue**)malloc(SIZE*sizeof(Queue*));
            int n;
            for(int j= 0; j<SIZE; j++){
                qq[j] = init();
            }
            fscanf(fp,"%d", &n);
            for(int j=0;j<n;j++){
                int t,m;
                fscanf(fp,"%d %d", &t, &m);
                Enqueue(fp,qq[m-1],&t,&m);
            }
            
            
            process(qq,&n,op);
            free(qq[0]);
            free(qq);
            
            }
            fclose(fp);
            fclose(op);
            return 0;
    }