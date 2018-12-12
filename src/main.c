#include "lex.c"
#include "syntax.c"


typedef struct constraintList {
    char * constraint;
    struct constraintList * next;
}T_ContraintList;

typedef struct portList {
    char * port;
    struct portList * next;
}T_PortList;

typedef struct stateList {
    char * state;
    struct stateList * next;
}T_StateList;

typedef struct Transition {
    char * startState;
    char * destState;
    struct portList * portList;
    struct constraintList * ConstraintList;
}T_Transition;

typedef struct TransitionList {
    T_Transition* transition;
    struct TransitionList * next;
}T_TransitionList;

typedef struct CA{
    T_TransitionList *  transitions;
    char * startState;
    T_StateList * states;
    T_PortList * ports;
}T_CA;

typedef struct Gamma {
    char * transition;
    struct Gamma * next;
}T_Gamma;

T_ContraintList * NewConstraintList();
T_PortList * NewPortList();
T_StateList * NewStateList();



T_Transition * setTransitionStartState (char *startState, T_Transition * t){
    t->startState= (char *)malloc(sizeof(char)*strlen(startState));
    strcpy(t->startState,startState);
    return t;
}
T_Transition * setTransitionDestState (char *destState, T_Transition * t){
    t->destState= (char *)malloc(sizeof(char)*strlen(destState));
    strcpy(t->destState,destState);
    return t;
}


T_Transition * CreateEmptyTranstion(){
    T_Transition * temp = (T_Transition *) malloc(sizeof(T_Transition));
    temp->startState = NULL;
    temp->destState = NULL;
    temp->portList = NewPortList();
    temp->ConstraintList = NewConstraintList();
    return temp;
}

T_TransitionList* newTransitionList(T_Transition * t){
    if (!t) return NULL;
    T_TransitionList* listNode = (T_TransitionList*) malloc(sizeof(T_TransitionList));
    listNode->transition = t;
    listNode->next = NULL;
    return listNode;
}

void appendTransition(T_TransitionList ** list, T_Transition* t){
    if(!t) return;

    if(! *list){
        *list = newTransitionList(t);
    }
    else{
        T_TransitionList* p = *list;
        while(p->next){
            p = p->next;
        }
        p->next = newTransitionList(t);
    }
}


T_CA * CreateEmptyCA(){
    T_CA * temp = (T_CA *) malloc(sizeof(T_CA));
    temp->startState = NULL;
    temp->transitions = NULL;
    temp->ports = NewPortList();
    temp->states = NewStateList();
    return temp;
}

T_CA * setCAState ( T_StateList * list,char *state){
    T_StateList * temp = list;
    while(temp->next){
        temp = temp->next;
    }
    if(temp->state ==NULL){
        temp->state= (char *)malloc(strlen(state)+1);
        strcpy(temp->state,state);
    }
    else {
        char concat[strlen(temp->state)];
        strcpy(concat, temp->state);
        temp->state = (char * ) malloc(strlen(concat) + strlen(state) + 1);
        temp->state[0] = '\0';
        strcat(temp->state, concat);
        strcat(temp->state, state);
    }

}

T_CA * setCAStartState (char *state, T_CA * t){
    if(t->startState ==NULL){
        t->startState= (char *)malloc(strlen(state)+1);
        strcpy(t->startState,state);
    }
    else {
        char temp[strlen(t->startState)];
        strcpy(temp, t->startState);
        t->startState = (char *) malloc(strlen(t->startState) + strlen(state) + 1);
        t->startState[0] = '\0';
        strcat(t->startState, temp);
        strcat(t->startState, state);
    }
    return t;
}



T_Gamma * NewGamma(char * trans){
    T_Gamma * temp = (T_Gamma *) malloc(sizeof(T_Gamma));
    temp->transition = (char*) malloc(sizeof(char)* strlen(trans));
    strcpy(temp->transition,trans);
    temp->next = NULL;
    return temp;
}

void GammaAppendtransition(T_Gamma ** Gamma,char * trans){

    if(!trans) return;

    if(! *Gamma){
        *Gamma = NewGamma(trans);
    }
    else{
        T_Gamma* p = *Gamma;
        while(p->next){
            p = p->next;
        }
        p->next = NewGamma(trans);
    }
}


T_StateList * NewStateList(){
    T_StateList * temp = (T_StateList *) malloc(sizeof(T_StateList));
    temp->state = NULL;
    temp->next = NULL;
    return temp;
}

void AppendState(T_StateList ** list){
    if(! *list){
        *list = NewStateList();
    }
    else{
        T_StateList* p = *list;
        while(p->next){
            p = p->next;
        }
        p->next = NewStateList();
    }
}













T_PortList * NewPortList(){
    T_PortList * temp = (T_PortList *) malloc(sizeof(T_PortList));
    temp->port = NULL;
    temp->next = NULL;
    return temp;
}

void AppendPort(T_PortList ** list){
    if(! *list){
        *list = NewPortList();
    }
    else{
        T_PortList* p = *list;
        while(p->next){
            p = p->next;
        }
        p->next = NewPortList();
    }
}

T_ContraintList * NewConstraintList(){
    T_ContraintList * temp = (T_ContraintList *) malloc(sizeof(T_ContraintList));
    temp->constraint = NULL;
    temp->next = NULL;
    return temp;
}

void AppendConstraint(T_ContraintList ** list){
    if(! *list){
        *list = NewConstraintList();
    }
    else{
        T_ContraintList* p = *list;
        while(p->next){
            p = p->next;
        }
        p->next = NewConstraintList();
    }
}


void AppendPortChars(T_PortList * list,char * extra){
    T_PortList * temp = list;
    while(temp->next){
        temp = temp->next;
    }
    if(temp->port ==NULL){
        temp->port= (char *)malloc(strlen(extra)+1);
        strcpy(temp->port,extra);
    }
    else {
        char concat[strlen(temp->port)];
        strcpy(concat, temp->port);
        temp->port = (char * ) malloc(strlen(concat) + strlen(extra) + 1);
        temp->port[0] = '\0';
        strcat(temp->port, concat);
        strcat(temp->port, extra);
    }
}



void AppendConstraintChars(T_ContraintList * list,char * extra){
    T_ContraintList * temp = list;
    while(temp->next){
        temp = temp->next;
    }
    if(temp->constraint ==NULL){
        temp->constraint= (char *)malloc(strlen(extra)+1);
        strcpy(temp->constraint,extra);
    }
    else {
        char concat[strlen(temp->constraint)];
        strcpy(concat, temp->constraint);
        temp->constraint = (char * ) malloc(strlen(concat) + strlen(extra) + 1);
        temp->constraint[0] = '\0';
        strcat(temp->constraint, concat);
        strcat(temp->constraint, extra);
    }
}



char * AppendChars(char * atual,char * extra){
    if(atual ==NULL){
        atual= (char *)malloc(strlen(extra)+1);
        strcpy(atual,extra);
    }
    else {
        char temp[strlen(atual)];
        strcpy(temp, atual);
        atual = (char * ) malloc(strlen(atual) + strlen(extra) + 1);
        atual[0] = '\0';
        strcat(atual, temp);
        strcat(atual, extra);
    }
    return atual;
}




void gerenateTransitionAux(Node * t,T_CA * CA,T_Transition * trans,int pos){
    if(t == NULL) return;
    if(trans == NULL) {
        trans = CreateEmptyTranstion();
    }

    if(t->content) {
        if(strcmp(t->content,"t_set") == 0){
            printf("  \n  ");
            appendTransition(&CA->transitions,trans);
            gerenateTransitionAux(t->child,CA,NULL,0);
            printf("  \n  ");
            return;
        }
        if(t->child==NULL) {
            if (strcmp(t->content, "set'") != 0 && strcmp(t->content, "F'") != 0 && strcmp(t->content, "T'") != 0 && strcmp(t->content, "E'") != 0 && strcmp(t->content, ":") != 0 ) {
                if( strcmp(t->content, ")") != 0 && strcmp(t->content, "]") != 0){
                    if (strcmp(t->content, "(") == 0) {
                        pos = 1;
                    }
                    else if(strcmp(t->content, ")")==0){
                        AppendPort(&trans->portList);
                    }
                    else if (strcmp(t->content, "[") == 0) {
                        pos = 2;
                    }
                    else if(strcmp(t->content, "]")==0){
                        AppendConstraint(&trans->ConstraintList);
                    }
                    else if (trans->startState == NULL) {
                        trans = setTransitionStartState(t->content, trans);
                    } else if (trans->destState == NULL) {
                        trans = setTransitionDestState(t->content, trans);
                    }else if(pos == 1){
                        if(strcmp(t->content, ",")==0){
                            AppendPort(&trans->portList);

                        }else{
                            AppendPortChars(trans->portList,t->content);
                        }
                    } else if(pos == 2){
                        if(strcmp(t->content, ",")==0){
                            AppendConstraint(&trans->ConstraintList);

                        }else{
                            AppendConstraintChars(trans->ConstraintList,t->content);
                        }
                    }
                }
            }
        }
    }
    if(t->child){
        gerenateTransitionAux(t->child,CA,trans,pos);
    }
    if(t->sibling) {
        gerenateTransitionAux(t->sibling,CA,trans,pos);
    }
}

void generateStates(Node * t,T_CA * CA){
    if(t == NULL) return;
    if(t->content) {
        if(t->child==NULL) {
            if (strcmp(t->content, "set'") != 0 &&strcmp(t->content, "STATES") != 0) {
                if(strcmp(t->content, ",") == 0){
                    AppendState(&CA->states);
                }else {
                    setCAState(CA->states, t->content);
                }
            }
        }
    }
    if(t->child){
        generateStates(t->child,CA);
    }
    if(t->sibling) {
        generateStates(t->sibling,CA);
    }
}

void generateStartStates(Node * t,T_CA * CA){
    if(t == NULL) return;
    if(t->content) {
        if(t->child==NULL) {
            if (strcmp(t->content, "set'") != 0 &&strcmp(t->content, "STATES") != 0 &&strcmp(t->content, "INITIAL") != 0) {
                CA = setCAStartState(t->content,CA);
            }
        }
    }
    if(t->child){
        generateStartStates(t->child,CA);
    }
    if(t->sibling) {
        generateStartStates(t->sibling,CA);
    }
}

void generatePorts(Node * t,T_CA * CA){
    if(t == NULL) return;
    if(t->content) {
        if(t->child==NULL) {
            if (strcmp(t->content, "set'") != 0 &&strcmp(t->content, "NAMES") != 0 ) {
                if(strcmp(t->content, ",")==0){
                    AppendPort(&CA->ports);

                }else{
                    AppendPortChars(CA->ports,t->content);
                }
            }
        }
    }
    if(t->child){
        generatePorts(t->child,CA);
    }
    if(t->sibling) {
        generatePorts(t->sibling,CA);
    }
}

void gerenateCA(Node * t,T_CA * list){
    if(t == NULL) return;
    if(t->content) {
        if(strcmp(t->content,"t_set") == 0) {
            gerenateTransitionAux(t->child, list, NULL, 0);
        }
        else{
            if(strcmp(t->content,"states") == 0){
                generateStates(t->child,list);
            }
            else if(strcmp(t->content,"istates") == 0){
                generateStartStates(t->child,list);
            }
            else if(strcmp(t->content,"names") == 0){
                generatePorts(t->child,list);
            }
            else if(t->child){
                gerenateCA(t->child,list);
            }
            if(t->sibling) {
                gerenateCA(t->sibling,list);
            }
        }
    }

}





T_Gamma * GenerateGamma(T_CA * CA){
    T_TransitionList * t = CA->transitions;
    char * entry = NULL;

    T_Gamma * Gamma = NULL;
    int index =0;
    while(t){
        entry = AppendChars(entry,t->transition->startState);
        entry = AppendChars(entry," && ");

        T_ContraintList * constraint = t->transition->ConstraintList;
        while(constraint){
            entry = AppendChars(entry,constraint->constraint);
            if(constraint->next){
                entry = AppendChars(entry," && ");
            }
            constraint= constraint->next;
        }
        entry = AppendChars(entry," && ");
        T_PortList * ports = t->transition->portList;
        while(ports){
            entry = AppendChars(entry,ports->port);
            if(ports->next){
                entry = AppendChars(entry," && ");
            }
            ports= ports->next;
        }
        entry = AppendChars(entry," && ");
        T_PortList * CAports = CA->ports;
        int contains = 0;
        while(CAports){
            contains = 0;
            ports = t->transition->portList;
            while(ports){
                if(strcmp(ports->port,CAports->port)==0) {
                    contains=1;
                }
                ports= ports->next;
            }
            if(contains == 0) {
                entry = AppendChars(entry,"NEG ");
                entry = AppendChars(entry,CAports->port);
                if(CAports->next){
                    entry = AppendChars(entry," && ");
                }
            }
            CAports = CAports->next;
        }

        if(strncmp(entry,"&&",strlen(entry)-3)==0){
            entry[strlen(entry)-3] = '\0';
        }

        entry = AppendChars(entry," <--> ");

        entry = AppendChars(entry," <t_");

        char str[12];
        sprintf(str, "%d", index);
        entry = AppendChars(entry,str);
        entry = AppendChars(entry,"> ");

        entry = AppendChars(entry,t->transition->destState);

        GammaAppendtransition(&Gamma,entry);
        entry[0]= '\0';
        t = t->next;
        index++;
    }
    t = CA->transitions;
    entry = NULL;
    index =0;
    while(t) {
        entry = AppendChars(entry,"NEG ");

        entry = AppendChars(entry,"<t_");
        char str[12];
        sprintf(str, "%d", index);
        entry = AppendChars(entry,str);
        entry = AppendChars(entry,"> ");

        str[12];
        sprintf(str, "%d", 1);
        entry = AppendChars(entry,str);
        if(t->next){
            entry = AppendChars(entry," && ");
        }else{
            entry = AppendChars(entry," ");
        }
        t = t->next;
        index++;
    }

    entry = AppendChars(entry," --> ");
    char str[12];
    sprintf(str, "%d", 0);
    entry = AppendChars(entry,str);
    GammaAppendtransition(&Gamma,entry);

    return Gamma;

}


int main(int argc, char *argv[]) {
    GenerateLex(argc, argv);
    GenerateTree(argc, argv);
    Node * n = syntaxTree;

    T_CA * CA =  CreateEmptyCA();
    gerenateCA(n,CA);
    T_Gamma * g = GenerateGamma(CA);



    FILE *dest = fopen(argv[4], "w");
    T_Gamma * temp = g;
    while(temp){
        fprintf(dest, "%s\n", temp->transition);
        temp = temp->next;
    }
    fclose(dest);

}
