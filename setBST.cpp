//Set implemented on a BinarySearchTree

#include <iostream>
#include <vector>
#include <algorithm>

struct Node
{
 int info;
 Node * left;
 Node * right;

 Node(int _info) //konstruktor
{
    info = _info;
    left = NULL;
    right = NULL;
}
};

class setBST
{
protected:
Node* root;

    void InOrder(Node* n){
        if(n!=NULL)
            {
                InOrder(n->left);
                std::cout << n->info << " ";
                InOrder(n->right);
            }
    };

    void InOrderToList(Node* n, std::vector<int>& L){
        if(n!=NULL)
            {
                InOrderToList(n->left, L);
                L.push_back(n->info);
                InOrderToList(n->right, L);
            }
    };

    Node* ListToBST(std::vector<int>& L, int b, int e)
    {
        if (b > e)
            return NULL;
 
        int mid = (b+e+1)/2;
        Node *n = new Node(L[mid]);
    
        n->left = ListToBST(L, b, mid - 1);
    
        n->right = ListToBST(L, mid + 1, e);
    
        return n;
    }
    

    int getSizeRec(Node* n){
        if (n == NULL)
        return 0;
        else
            return(getSizeRec(n->left) + getSizeRec(n->right)) +1;
    }; 
    bool isInSetRec(Node*n, int x){
        if(n == NULL) return false;
        if(n->info == x) return true;
        if (n->info < x)
            return isInSetRec(n->right, x);
        return isInSetRec(n->left, x);
    }; 

    void withdrawNode(Node* n, Node* parent, bool isLeft) //usuwamy wezel - znajac wezel i jego rodzica i wiedzac czy jest lewym dzieckiem - funkcja pomocnicza do withdraw
    {
        if(n->right == NULL && n->left == NULL) //jesli wezel nie ma dzieci
        {
            if(isLeft) //i jest lewym dzieckiem 
            {
                parent->left = NULL; //lewe dziecko rodzica to NULL
                return;
            }
            parent->right = NULL; //jesli jest prawym dzieckiem to prawe dziecko rodzica to NULL
            return;
        }
        if(n->right == NULL)//jesli ma tylko lewe dziecko
        {
            if(isLeft) //i jest lewym
            {
                parent->left = n->left; //jego lewe (jedyne) dziecko to teraz lewe dziecko rodzica
                return;
            }
            parent->right = n->left; //byl prawym dzieckiem, wiec jego lewe (jedyne) dziecko to teraz prawe dziecko rodzica
            return;
        }
        if(n->left == NULL) //jesli ma tylko prawe dziecko to analogicznie jak wyzej
        {
            if(isLeft)
            {
                parent->left = n->right;
                return;
            }
            parent->right = n->right;
            return; 
        }
        //jesli ma oba dzieci
        Node* successor = n->right;
        Node* successorParent = n;
        bool isSuccesorLeft = false;
        while(successor->left != NULL)
        {
            successorParent = successor;
            successor = successor->left;
            isSuccesorLeft = true;
        } //znajdujemy nastepny w kolejnosci rosnacej wezel po usuwanym
        n->info = successor->info; //przepisujemy wartosc nastepnika do usuwanego
        withdrawNode(successor, successorParent, isSuccesorLeft); //usuwamy nastepnik
    }

    void withdrawRoot() //usuwanie korzenia funkcja pomocnicza
    {
        if(root->left == NULL)
        {
            root = root->right;
            return;
        }
        if(root->right == NULL)
        {
            root = root->left;
            return;
        }
        //jesli ma oba dzieci
        Node* successor = root->right;
        Node* successorParent = root;
        bool isSuccesorLeft = false;
        while(successor->left != NULL)
        {
            successorParent = successor;
            successor = successor->left;
            isSuccesorLeft = true;
        } //znajdujemy nastepny w kolejnosci rosnacej wezel po usuwanym
        root->info = successor->info; //przepisujemy wartosc nastepnika do usuwanego
        withdrawNode(successor, successorParent, isSuccesorLeft); //usuwamy nastepnik
    }

    void MAKENULL(Node* p)
    {
        if(p!=NULL)
        {
            MAKENULL(p->left);
            MAKENULL(p->right);
            delete p;
        }
};

public:
    void clearSet()
    {
        MAKENULL(root);
        root = NULL;
    }

    setBST()
    {
        root = NULL;
    }

    int getSize(){
        return getSizeRec(root);
    }; 

    void printSet(){
        if(root == NULL) return;
        InOrder(root);
        std::cout<<std::endl;
    }; 

    void insert(int x){
        Node* N = new Node(x);
        if(root == NULL) root = N;

        Node* n = root;
        Node* parent = NULL;
        while(n!=NULL) //dopoki nie dojdziemy do konca jakiejs galezi
        {
            parent = n;
            if(x < n->info)
            {
                n = n->left; //jesli wartosc ktora wstawiamy jest mniejsza od tej na ktorej jestesmy to idziemy w lewo
            }
            else
            {
                n = n->right; //jesli nie to w prawo
            }
        }
        if(x < parent->info) //jesli wartosc do wstawienia jest mniejsza niz wartosc na koncu galezi
        {
            parent->left = N; //to wstawiamy w lewo
            return;
        }
        if(x > parent->info)
        {
            parent->right = N; //jesli nie to w prawo
            return;
        }
        return;
    };
    void withdraw(int x)
    {
        Node* n = root;
        Node* parent = NULL;
        bool isLeft = false;
        while(n!=NULL) //dopoki nie dojdziemy do konca galezi
        {
            if(n->info == x) //jesli wartosc sie zgadza to wychodzimy z petli
            {
                break;
            }
            parent = n; //przepinamy rodzica na to gdzie jestesmy
            if(x < n->info) //jesli szukana wartosc jest mniejsza
            {
                n = n->left; //to idziemy w lewo
                isLeft = true;
            }
            else
            {
                n = n->right; //jesli wieksza lr to w prawo
                isLeft = false;
            }
        }
        if(n==NULL) //jesli nie znalezlismy wartosci
        {
            return;
        }
        if(root == n) //jesli wartosc byla w korzeniu
        {
            withdrawRoot(); //usuwamy korzen
            return;
        }
        withdrawNode(n, parent, isLeft); //znalezlismy wartosc - mamy wezel w ktorym jest i rodzica tego wezla
    };
    bool isInSet(int x){
        return isInSetRec(root, x);
    }; 

    setBST operator+(setBST& obj){
        if(this->root == NULL) return obj;
        if(obj.root == NULL) return *this;
        std::vector<int> T1;
        std::vector<int> T2;

        this->InOrderToList(this->root, T1);
        obj.InOrderToList(obj.root, T2);
        T1.insert(T1.end(), T2.begin(), T2.end());
        std::sort(T1.begin(), T1.end());

        auto j = std::unique(T1.begin(), T1.end());
            T1.erase(j, T1.end());

        setBST res;
        res.root = ListToBST(T1, 0, T1.size() - 1);
        return res;
    };
    setBST operator*(setBST& obj){
        setBST res;
        if(this->root == NULL) return res;
        if(obj.root == NULL) return res;
        std::vector<int> T1;
        std::vector<int> T2;
        std::vector<int> T3;
        this->InOrderToList(this->root, T1);
        obj.InOrderToList(obj.root, T2);

        std::vector<int>::iterator i;
        std::vector<int>::iterator j = T2.begin();
        for(i = T1.begin(); i != T1.end(); ++i)
        {
            while(*j < *i){
                if(j == T2.end())
                    {
                        res.root = ListToBST(T3, 0, T3.size() - 1);
                        return res;
                    }
                j++;
            }
            if(*i == *j)
                {
                    T3.push_back(*i);
                }
        }
        res.root = ListToBST(T3, 0, T3.size() - 1);
            return res;
    };   
    setBST operator-(setBST& obj){
        setBST res;
        if(this->root == NULL) return res;
        if(obj.root == NULL) return *this;
        std::vector<int> T1;
        std::vector<int> T2;
        this->InOrderToList(this->root, T1);
        obj.InOrderToList(obj.root, T2);

        std::vector<int>::iterator i;
        std::vector<int>::iterator j = T2.begin();
        for(i = T1.begin(); i != T1.end(); ++i)
        {
            while(*j < *i){
                if(j == T2.end())
                    {
                        res.root = ListToBST(T1, 0, T1.size() - 1);
                        return res;
                    }
                j++;
            }
            if(*i == *j)
                {
                    T1.erase(i);
                    i--;
                }
        }
        res.root = ListToBST(T1, 0, T1.size() - 1);
            return res;
    };
    bool operator==(setBST& obj){
        if(this->root == NULL && obj.root == NULL) return true;
        if(this->root == NULL && obj.root != NULL) return false;
        if(obj.root == NULL) return false;
        std::vector<int> T1;
        std::vector<int> T2;
        this->InOrderToList(this->root, T1);
        obj.InOrderToList(obj.root, T2);
        if(T1.size() != T2.size()) return false;

        std::vector<int>::iterator i;
        std::vector<int>::iterator j = T2.begin();
        for(i = T1.begin(); i != T1.end(); ++i, j++){
            if(*i != *j) return false;
        }
        return true;
    };  
    bool operator<=(setBST& obj){
        if(this->root == NULL) return true;
        if(this->root != NULL && obj.root == NULL) 
            return false;
        std::vector<int> T1;
        this->InOrderToList(this->root, T1);
        if(T1.size() > obj.getSize()) return false;
        std::vector<int>::iterator i;
        for(i = T1.begin(); i != T1.end(); ++i){
            if(!obj.isInSet(*i))
                return false;
        }
        return true;
    };
};

int main(){
    setBST A;
    A.insert(5);
    A.insert(3);
    A.insert(8);
    A.insert(1);
    A.insert(10);
    A.insert(9);
    A.insert(4);
    A.insert(10);
    A.printSet();
    std::cout << A.getSize() << std::endl;
  
    setBST B;
    setBST C = A+B;
    C.printSet();

    B.insert(7);
    B.insert(2);
    B.insert(4);
    B.insert(1);
    B.insert(12);
    B.insert(9);
    B.insert(4);
    B.insert(10);
    B.printSet();

    C = A+B;
    C.printSet();
    setBST D = A*B;
     D.printSet();
    setBST E = A-B;
     E.printSet();
   setBST F = C*A;
   F.printSet();
    setBST G = B-A;
     G.printSet();
   if(F==A) std::cout << "TAK" << std::endl;
    else std::cout << "NIE" << std::endl;
    A.printSet();
    F.printSet();
    if(A <= F) std::cout << "TAK" << std::endl;
    else std::cout << "NIE" << std::endl;
    if(D <= A) std::cout << "TAK" << std::endl;
    else std::cout << "NIE" << std::endl;
    if(C <= B) std::cout << "TAK" << std::endl;
    else std::cout << "NIE" << std::endl;
    if(A <= C) std::cout << "TAK" << std::endl;
    else std::cout << "NIE" << std::endl;
    if(C <= B) std::cout << "TAK" << std::endl;
    else std::cout << "NIE" << std::endl;
     if(E <= G) std::cout << "TAK" << std::endl;
    else std::cout << "NIE" << std::endl;
     if(G <= E) std::cout << "TAK" << std::endl;
    else std::cout << "NIE" << std::endl;
     if(A==B) std::cout << "TAK" << std::endl;
    else std::cout << "NIE" << std::endl;

    if(G==A) std::cout << "TAK" << std::endl;
    else std::cout << "NIE" << std::endl;

    A.clearSet();
    A.printSet();
}