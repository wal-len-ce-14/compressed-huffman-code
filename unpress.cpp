#include<bits/stdc++.h>
using namespace std;

#define block 16
#define pr "presstext.txt"
#define ot "unpresstest.txt"

int size;
string code;

struct Node{
	bool sign;
	char ch;
	Node *left, *right;
	Node(bool s, char c){
		sign = s;
		ch = c;
		left = nullptr;
		right = nullptr;
	}
	void set_left(Node *n){
		left = n;
	}
	void set_right(Node *n){
		right = n;
	}
	bool DFS(Node *root, char c){
		if(root == nullptr){
			if(DFS(right, c)){
				return true;
			}else if(DFS(left, c)){
				return true;
			}
		}else if(root->ch != 0x01){
			if(c == root->ch){
				if(ch == 0x0D);
				else if(c == 0x01){
//					printf("-- %d", c, root->sign);
				}
				else if(c == 0x0A){
//					printf("\\n %d", root->sign);
				}else if(c == 0x20){
//					printf("\\s %d", root->sign);
				}else{
//					printf("%2c %d", c, root->sign);
				}
				if(root->sign){
					code += "1";
				}else{
					code += "0";
				}
				
				
				return true;
			}else return false;
		}else if(root->ch == 0x01){
//			printf("->(%d) ", root->sign);
			if(DFS(root->right, c)){
//				printf("%d", root->sign);
				if(root->sign){
					code += "1";
				}else{
					code += "0";
				}
				return true;
			}else if(DFS(root->left, c)){
//				printf("%d", root->sign);
				if(root->sign){
					code += "1";
				}else{
					code += "0";
				}
				return true;
			}
		}
		return false;
	}
	void search(char c){
		int i = 0;
		if(!DFS(nullptr, c)){
			cout << "Error: cant find " << c;
		}
	}
}; 


Node* build_Haffman(char *p){
	fstream filep;
	filep.open(p, ios::in);
	if (!filep) {
        std::cerr << "FileP could not be opened!" << std::endl;
    }
	Node *root = new Node(0, 0x00);
	Node *cur = root;
	char a;
	filep >> size;
	cout << "#file size " << size << endl;
	filep.ignore();
	while(filep.get(a)){	// 檔案字元 
		if(a != 0x0A && a != 0x0D){	// 換行符為不同section分割點 
			if(a != '\''){			 
				if(a == '0'){		// 新節點往左
					if(cur->left == nullptr){ 	 
						Node *n = new Node(0, 0x01);
						cur->set_left(n);
						cur = n;
					}else{			// 節點已存在 
						cur = cur->left;
					}
				}else if(a == '1'){	// 新節點往右
					if(cur->right == nullptr){
						Node *n = new Node(1, 0x01);
						cur->set_right(n);
						cur = n;
					}else{			// 節點已存在 
						cur = cur->right;
					}
				}
			}else if(a == '\''){	// "'"字元 表示葉節點的字元
				short int ch;
				filep >> ch;		// 讀整數(字元以整數儲存) 
				cur->ch = char(ch);	// 葉節點存實際字元 
				cur = root;			
				filep.ignore();		// 忽略右邊 "'" 
			}
		}else break;
	}
	
	filep.close();
	return root;
}

void unpress(char *p, char *out, Node *root){
	fstream file, fileout;
	file.open(p, ios::in);
	fileout.open(out, ios::out);
	if(!file || !fileout){
		std::cerr << "File could not be opened!" << std::endl;
	}
	char c;
	while(file.get(c)){		// 跳過 file size 標頭 
		if(c == '\n' || c == ' ') break;
	}			
	cout << endl;
	while(file.get(c)){		// 跳過 huffman code 標頭 
		if(c == '\n' || c == ' ') break;
	}
	cout << endl;
	
	int i;
	unsigned int a;
	Node *cur = root;
	while(file >> a && size != 0){	// 讀整數 size => file_size  
		i = 32;
		while(i != 0 && size != 0){	
			if(a & 0x80000000){		// 必較最左位元 1為右 0為左(看解壓樹生成方式) 
				cur = cur->right;
			}else{
				cur = cur->left;
			}
			a = a << 1;				
			i--;
			if(cur->ch != 0x00 && cur->ch != 0x01){	// 發現非中間節點位元 
				printf("%c", cur->ch);
				fileout << cur->ch;
				cur = root;
				size--;  		// 輸出字元並減一個檔案大小 表解出一字 
			}
		}
	}
	

	
	file.close();
	fileout.close();
}

int main(){
	Node *root = build_Haffman(pr);
	unpress(pr, ot, root);
	return 0;
}
