#include<iostream>
using namespace std;
class node{
public:
	int data;
	node* left;
	node* right;
	node* parent;
	node(int value){
		data=value;
		left=NULL;
		right=NULL;
		parent=NULL;
	}
};
class BST{
public:
	node* root;
	BST(){
		root=NULL;
	}
	void insertHelper(int value){
		insert(root,value);
	}
	void insert(node* curr,int value){
		//Base case if curr is NULL ,insert there
		if(root==NULL){
			 root =new node(value) ;                                                                      
			return;
		}
		//Else compare the curr data with value
		else if (value  <  curr->data){
		//if curr data > value ==> move right and call insert
			if(curr->left==NULL){
					curr->left=new node(value);
					curr->left->parent=curr;}
			else
				insert(curr->left,value);
		}
		else{	
		//else move right and call insert
			if(curr->right==NULL){
				curr->right=new node(value);
				curr->right->parent=curr;}	
			else
				insert(curr->right,value);
		}
		
	}
	void displayHelper(){
		display(root);cout<<endl;
	}
	void display(node * curr){
		if (curr == NULL) return;
		//display left
		display(curr->left);
		//display current
		cout<<curr->data<<",";
		//display right
		display(curr->right);
	}
	node* searchHelper(int no){
	return search(root,no);
	}
	node* search(node * curr, int value){
			if (curr == NULL || curr->data == value) return curr;
			else if (value < curr->data)
				//search for number in left
				return search(curr->left,value);
				//search number in right
			else 
				return search(curr->right,value);
	}
	/*node* parent(int no){
	return parent2(root,no);
	}
	node* parent2(node * curr, int value){
			if (curr == NULL || curr->data == value) return curr-> parent;
			else if (value < curr->data)
				//search for number in left
				return parent2(curr->left,value);
				//search number in right
			else 
				return parent2(curr->right,value);
	}*/
	node* find_minHelper(int m){
	node * roo=searchHelper(m);find_min(roo);
	}
	node* find_min(node * curr){
	    	if (curr->left == NULL || curr->right == NULL) {
				return curr;
				}
				//search number in right
			else 
				{return find_min(curr->left);}
	}
	int count(){int cou=0;count2(root,cou);return cou;}
	int count2(node * curr,int i){
		
		if (curr == NULL) return i;
			
			count2(curr->left,i);
			i++;
			count2(curr->right,i);
	}
	void replace_At_ParentH(int A,int B){
		node* a=searchHelper(A);node* b=searchHelper(B);
		replace_At_Parent(a,b);
	}
	void replace_At_Parent(node*A,node*B){
		if(A->parent->data < A->data){
			//node*P=A->parent;//delete A;
			A->parent->right=B;
			B->parent=A->parent;
			}
		else
		{
			//node*P=A->parent;//delete A;
			A->parent->left=B;
			B->parent=A->parent;
		}
	}
	//void 
	/*search 4 --if 2 kids---temp= min of right hand side-- replace that node ---than delete*/
	void print2DUtil(node*root, int space){  
        // Base case  
        if (root == NULL)  
            return;  
        // Increase distance between levels  
        space += 5;  
        // Process right child first  
        print2DUtil(root->right, space);  
    	// Print current node after space  
        // count  
        cout<<endl;  
        for (int i = 5; i < space; i++)  
            cout<<" ";  
        cout<<root->data<<"\n";  
    	// Process left child  
        print2DUtil(root->left, space);  
	}  
	// Wrapper over print2DUtil()  
	void print2D(){
		// Pass initial space count as 0  
		print2DUtil(root, 0);  
		cout << endl;
		
	    }
	void binary_delete(node * curr, int key){
       node*del=search(curr,key);
	   
	    //if key is the root
		if(del==root){
			if(del->left==NULL and del->right==NULL){//if root has no children
				delete del;
				}
			else if(del->left==NULL or del->right==NULL){//if root have only one children
				if(del->left!=NULL) {	root=del->left;delete del;}
				else
				{
						root=del->right;delete del;
				}
				
			}
		}
		//case for no children
		else if(del->left==NULL and del->right==NULL){
				if(del->data > del->parent->data){
					del->parent->right=NULL;delete del;
				}
				else
				{
					del->parent->left=NULL;delete del;
				}
				
		}
		//case for only one child
		else if(del->left==NULL or del->right==NULL){
			if(del->left!=NULL){
				replace_At_Parent(del,del->left);delete del;
			}
			else{
				replace_At_Parent(del,del->right);delete del;
			}
		}
		//case for two children
		else{
			node* min=find_min(del->right);
			
			if(min->left==NULL and min->right==NULL){cout<<"H";
				if(min->data>min->parent->data){
					del->data=min->data;min->parent->right=NULL;delete min;
				}
				else
				{
					del->data=min->data;min->parent->left=NULL;delete min;
				}	
			}
			else if(min->left==NULL or min->right==NULL){
				if(min->data>min->parent->data){
					del->data=min->data;
					if(min->left!=NULL){
						min->parent->right=min->left;delete min;
					}
					else{
						min->parent->right=min->right;delete min;
					}
				}
				else
				{
					del->data=min->data;
					if(min->left!=NULL){
						min->parent->left=min->left;delete min;
					}
					else{
						min->parent->left=min->right;delete min;
					}
				}
			}
			else
			{
				binary_delete(min,min->data);
			}
			
		}

	}
};


int main(){
    BST bst1;
    bst1.insertHelper(4);
    bst1.insertHelper(2);
    bst1.insertHelper(3);
    bst1.insertHelper(1);
    bst1.insertHelper(6);
    bst1.insertHelper(5);
    bst1.insertHelper(7);
	bst1.insertHelper(8);
	*bst1.displayHelper();
    if(bst1.searchHelper(3) != NULL){
        cout << endl << bst1.searchHelper(3)->data << endl;
    }
	bst1.print2D();
    bst1.binary_delete(bst1.root,5);
    bst1.print2D();
    bst1.binary_delete(bst1.root,6);
    bst1.print2D();
    cout << "Deleting 2" << endl;
    bst1.binary_delete(bst1.root,2);
    bst1.print2D();
    bst1.binary_delete(bst1.root,4);
    bst1.print2D();
    bst1.binary_delete(bst1.root,7);
    bst1.print2D();
    bst1.binary_delete(bst1.root,8);
    bst1.print2D();
    bst1.binary_delete(bst1.root,3);
    bst1.print2D();
    bst1.binary_delete(bst1.root,1);
    bst1.print2D();
    bst1.binary_delete(bst1.root,1);
    bst1.print2D();
    return 0;
}


