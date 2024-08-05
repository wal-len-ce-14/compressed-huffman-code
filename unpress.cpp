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
	while(filep.get(a)){	// �ɮצr�� 
		if(a != 0x0A && a != 0x0D){	// ����Ŭ����Psection�����I 
			if(a != '\''){			 
				if(a == '0'){		// �s�`�I����
					if(cur->left == nullptr){ 	 
						Node *n = new Node(0, 0x01);
						cur->set_left(n);
						cur = n;
					}else{			// �`�I�w�s�b 
						cur = cur->left;
					}
				}else if(a == '1'){	// �s�`�I���k
					if(cur->right == nullptr){
						Node *n = new Node(1, 0x01);
						cur->set_right(n);
						cur = n;
					}else{			// �`�I�w�s�b 
						cur = cur->right;
					}
				}
			}else if(a == '\''){	// "'"�r�� ��ܸ��`�I���r��
				short int ch;
				filep >> ch;		// Ū���(�r���H����x�s) 
				cur->ch = char(ch);	// ���`�I�s��ڦr�� 
				cur = root;			
				filep.ignore();		// �����k�� "'" 
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
	while(file.get(c)){		// ���L file size ���Y 
		if(c == '\n' || c == ' ') break;
	}			
	cout << endl;
	while(file.get(c)){		// ���L huffman code ���Y 
		if(c == '\n' || c == ' ') break;
	}
	cout << endl;
	
	int i;
	unsigned int a;
	Node *cur = root;
	while(file >> a && size != 0){	// Ū��� size => file_size  
		i = 32;
		while(i != 0 && size != 0){	
			if(a & 0x80000000){		// �����̥��줸 1���k 0����(�ݸ�����ͦ��覡) 
				cur = cur->right;
			}else{
				cur = cur->left;
			}
			a = a << 1;				
			i--;
			if(cur->ch != 0x00 && cur->ch != 0x01){	// �o�{�D�����`�I�줸 
				printf("%c", cur->ch);
				fileout << cur->ch;
				cur = root;
				size--;  		// ��X�r���ô�@���ɮפj�p ��ѥX�@�r 
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
