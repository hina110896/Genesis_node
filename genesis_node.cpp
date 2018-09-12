#include<bits/stdc++.h>
#include <iostream>
#include <time.h>
#include<vector>
#include<string.h>
using namespace std;
struct Owner{
	string name;
	string address;
	string mobile;
	string phone;
	float value;
	string password;
	int ownerNumb;
	
};
struct Node{
	time_t dt;
	Owner *owner;
	int nodeNumb;
	int nodeId;
	Node *refNodeId;
	vector<int> childNodeId;
	vector<Node*> refChildNodeId;
	
};
Node *getNode(int num,Owner *own){
	Node *np=new Node;
	np->dt=time(0);
	np->owner=own;
	np->nodeNumb=num;
	np->nodeId=(num);
	vector<Node*> v;
	np->refChildNodeId=v;
	np->refNodeId=NULL;
	vector<int> s;
	np->childNodeId=s;
	return np;
}

void query3(Node *child,int id,vector<Node*> &v){
	for(int i=0;i<v.size();i++){
		if(v[i]->nodeId==id){
			v[i]->refChildNodeId.push_back(child);
			v[i]->childNodeId.push_back(child->nodeId);
			child->refNodeId=v[i];
			break;
		}	
	}
}
string encrypt(string st,int n){
	string sol=st;
	for(int i=0;i<sol.length();i++){
		sol[i]+=n;
	}
	return sol;
}
string decrypt(string data,int n){
	string sol=data;
	for(int i=0;i<sol.length();i++){
		sol[i]-=n;
	}
	return sol;
}
Owner *getOwner(int num,string name1, string address1, string mobile1, string phone1, float value1,string pass1){
	
	Owner *own=new Owner;
	own->ownerNumb=num;
	own->address=encrypt(address1,num);
	own->address=encrypt(name1,num);
	own->address=encrypt(mobile1,num);
	own->address=encrypt(phone1,num);
	own->value=value;
	own->password=encrypt(pass1,num);
	return own;	
}
bool query4(vector<Owner*> &owners,Owner *currOwner,vector<Node*> &v){
	cout<<"enter NodeId: ";
			int id;
			cin>>id;
			bool f=false;
			for(int i=0;i<v.size();i++){
				if(v[i]->nodeId==id){
					if(currOwner==v[i]->owner){
						f=true;
					}
					break;
				}	
			}
		
			return f;
}
//deleting particular node using nodeId
void query5(vector<Owner*> &owners, Owner *currOwner, vector<Node*> &v){
	cout<<"Enter nodeId"<<endl;
	int id;
	cin>>id;
	bool f=false;
	for(int i=0;i<v.size();i++){
		if(v[i]->nodeId==id){
			if(query4(owners,currOwner,v)){
				
				f=true;
				Node *parent=v[i]->refNodeId;
				vector<Node*> child=parent->refChildNodeId;
				for(int k=0;k<child.size();k++){
					if(child[k]->nodeId==id){
						child.erase(child.begin()+i);
						
						break;
					}
				}
				
			}else{
				cout<<"Owner not recognized"<<endl;
				return;
			}
			break;
		}
	}
	if(f){
		cout<<"node removed"<<endl;
	}else{
		cout<<"not found"<<endl;
	}
}
void query6(vector<Owner*> &owners,Owner *currOwner, vector<Node*> &v){
	cout<<"Enter NodeId and UserId: "<<endl;
	int id,userIden;
	cin>>id>>userIden;
	bool f=false;
	for(int i=0;i<v.size();i++){
		if(v[i]->nodeId==id){
			if(query4(owners,currOwner,v)){
				
				
				Node *np=v[i];
				for(int k=0;k<owners.size();k++){
					if(owners[k]->ownerNumb==userIden){
						np->owner=owners[k];
						f=true;
						break;
					}	
				}
				
			}else{
				cout<<"You are not the owner of this node"<<endl;
				return;
			}
			break;
		}
	}
	if(f){
		cout<<"Node Owner changed"<<endl;
	}else{
		cout<<"Node not found"<<endl;
	}
}
void query7(vector<Node*> v){
	
}
void dfs(Node *root,int &n,int nums){
	if(root==NULL){
		n=max(n,nums);
	}
	int count=nums+1;
	vector<Node*> child=root->refChildNodeId;
	for(int i=0;i<child.size();i++){
		dfs(child[i],n,nums+1);
	}
	n=max(n,count);
}
void mergeSet(vector<Node*> &first, vector<Node*> &second,Owner *currOwner){
	//merge sets of same owner
	int i=0,j=0;
	while(i<first.size() && j<second.size()){
		while(i<first.size() && first[i]->owner!=currOwner){
			i++;
		}
		while(j<second.size() && second[j]->owner!=currOwner){
			j++;
		}
		int n1=-1,n2=-1;
		dfs(second[j],n2,0);
		dfs(first[i],n1,0);
		if(n1>n2){
			second[j]->refNodeId=first[i];
			first[i]->refChildNodeId.push_back(second[j]);
			second.erase(second.begin()+j);
			i++;
		}else{
			first[i]->refNodeId=second[j];
			second[j]->refChildNodeId.push_back(first[i]);
			second.erase(second.begin()+j);
			j++;
		}
	}
	
}
int main(){
	St:
    int num=0,nOwners=0;
    vector<vector<Node*> > set;
    vector<Node*> v;
    vector<Owner*> owners;
    int q;

    Owner *currOwner;
    bool f=false;
    
    while(!f){
    	cout<<"Enter: 1 to login / 2 to signup";
    	
    cin>>q;
    	if(q==1){
			cout<<"Enter Password and key";
	    	string pass;
	    	int key;
	    	cin>>pass;
	    	cin>>key;
	    	for(int i=0;i<owners.size();i++){
	    		if(owners[i]->ownerNumb==key){
	    			if(pass==decrypt(owners[i]->password,owners[i]->ownerNumb)){
	    				f=true;
	    				currOwner=owners[i];
	    				break;
					}
				}
			}
			cout<<"LOGIN failed"<<endl;
		}else{
			cout<<"Enter name, address, mobile,phone, value, password:"<<endl;
			string name,address,mobile,phone,pass;
			float value;
			cin>>name>>address>>mobile>>phone;
			cin>>value;
			cin>>pass;
			currOwner=getOwner(nOwners++,name, address, mobile, phone, value,pass);
			owners.push_back(currOwner);
			cout<<"your key is "<<currOwner->ownerNumb<<endl;
			f=true;
		}
	}
    
    
    while(1){
    	cout<<"Enter the Query: ";
		cin>>q;
		if(q==1){
			//create genesis node 
			vector<Node*> v;
			v.push_back(getNode(num++,currOwner));
			set.push_back(v);
		}else if(q==2){
			//push a set of child nodes
			int n=0;
			cout<<"Enter the number of nodes: ";
			cin>>n;
			vector<Node*> v(1);
			for(int i=0;i<n;i++){
				v[0]=(getNode(num++,currOwner));	
				set.push_back(v);
			}
			cout<<"nodes pushed"<<endl;
		}else if(q==3){
			//adding node to any set
			Node *np=getNode(num++,currOwner);
			v.push_back(np);
			cout<<"Enter setNo: ";
			int setNo;
			cin>>setNo;
			set[setNo].push_back(np);
			
		}else if(q==4){
			//verify owner
			bool f=false;
			for(int i=0;i<set.size();i++){
				f=query4(owners,currOwner,set[i]);
				if(f){
					cout<<"you are the owner!"<<endl;
				}		
			}
			if(!f){			
				cout<<"you are not owner"<<endl;
			}
		}else if(q==5){
			//edit the node/ delete node 
			query5(owners,currOwner,v);
			
		}else if(q==6){
			// transfer owner
			query6(owners,currOwner,v);
			
			
		}else if(q==7){
			//longest chain of genesis node
			int mx=-1;
			for(int i=0;i<set.size();i++){
				
				dfs(set[i][0],mx,0);	
			}
			cout<<"max chain="<<mx<<endl;
			
		}else if(q==8){
			//longest chain of sub node
			cout<<"enter node id"<<endl;
			int id;
			cin>>id;
			int ans=-1;
			bool f=false;
			for(int i=0;i<set.size();i++){
				for(int j=0;j<set[i].size();j++){
					if(set[i][j]->nodeId==id){
						f=true;
						dfs(set[i][j],ans,0);
						break;
					}
				}
				if(f){
					break;	
				}
			}
		}else if(q==9){
			//merge nodes
			cout<<"Enter 1st and 2nd set no."<<endl;
			int f,s;
			cin>>f>>s;
			mergeSet(set[f],set[s],currOwner);
			
		}else if(q==10){
			//log out
			currOwner=NULL;
			goto St;
		}else {
			break;
		}
	}
    return 0;
}
