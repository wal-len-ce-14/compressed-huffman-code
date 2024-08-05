#include<bits/stdc++.h>
using namespace std;

#define pr "test.txt"
#define ot "presstext.txt"

int fq[200] = {0};
string code;

void readfile_b(char p[50], bool prin){
    int i = 0;
    if(prin){
	    printf("    ");
	    for(int j = 0; j < 16; j++){
	    	printf("%5d", j+1);
		}	
	}
	
	fstream file;
	file.open(p, ios::in | ios::ate); 
	if (!file) {
        std::cerr << "File could not be opened!" << std::endl;
    }
	std::streamsize fileSize = file.tellg();
    file.seekg(0, ios::beg);
	char a;
    while(file.get(a)){
    	if(prin){
    		if(i < 16*5 || i >= fileSize-16*7-fileSize%16){
    			if(i == fileSize-16*7-fileSize%16){
    				printf("\n\t...\n\t...\n\t...\n");
				}
    			if(i % 16 == 0){
		    		cout << endl;
		    		printf("%4X  ", i);
				}
		    	
		    	if(a != 0x0D && (a >= 0x20 && a <= 0x7E) || a == 0x0A){
		    		printf("0x%2X ", a);
				}
			}
    		i++;
		}
    	fq[a]++;
	}
	file.close();
	if(prin) cout << "\n    #############################################################################\n";
}

void readfile_c(char p[50]){
	fstream file;
	file.open(p, ios::in | ios::ate);
	if (!file) {
        std::cerr << "File could not be opened!" << std::endl;
    }
    
    std::streamsize fileSize = file.tellg();
    file.seekg(0, ios::beg);
    
    char a;
    int i = 0;
    printf("\n    ");
    for(int j = 0; j < 16; j++){
    	printf("%5d", j+1);
	}
    while(file.get(a)){
    	if(i < 16*5 || i >= fileSize-16*7-fileSize%16){
    		if(i == fileSize-16*7-fileSize%16){
				printf("\n\t...\n\t...\n\t...\n");
			}
    		if(i % 16 == 0){
	    		cout << endl;
	    		printf("%4X  ", i);
			}
	    	if(a != 0x0D && (a >= 0x20 && a <= 0x7E) || a == 0x0A){
	    		if(a == 0x0A){
					printf("ch\\n ");
				}else if(a == 0x20){
					printf("ch\\s ");
				}else{
					printf("ch%2c ", a);
				}
	    		
			}
		}
    	i++;
    	
//		cout << a;
	}
	file.close();
	cout << "\n    #############################################################################\n\n";
}

int file_size(char p[50]){
	fstream file(p, std::ios::in | ios::ate);
	int s = file.tellg();
	file.close();
	return s;
}

void clearfile(char p[50]){
	fstream file;
	file.open(p, ios::out);
	if (!file) {
        std::cerr << "File could not be opened!" << std::endl;
    }	
    file.clear();
	file.close();
}

void writeINT(char p[50], int n){
	fstream file;
	file.open(p, ios::app);
	if (!file) {
        std::cerr << "File could not be opened!" << std::endl;
    }
    file << n << '\n';
    
    file.close();
}

void writefile(char p[50], char ch, string code){
	fstream file;
	file.open(p, ios::app);
	if (!file) {
        std::cerr << "File could not be opened!" << std::endl;
    }
    file << code << "'" << int(ch) << "'";
    
    file.close();
}

void readfile(char p[50], bool prin){
	readfile_b(p, prin);
	if(prin){
		readfile_c(p);
	}
}

struct myChar{
	char ch;	// �w�q�C�Ӧr�� 
	int fq;		// �w�q�C�Ӧr���X�{�W�v 
	myChar(){
		ch = 0x00;
		fq = 0;
	}
	void set(char c, int f){ ch = c; fq = f; }
	
	
	void leave(int f){ ch = 0x01; fq = f; }
	
	
	void show(){
		if(ch != 0x00){
			if(ch == 0x0D);
			else if(ch == 0x01){
				printf("-- %4d\n");
			}
			else if(ch == 0x0A){
				printf("\\n %4d\n", fq);
			}else if(ch == 0x20){
				printf("\\s %4d\n", fq);
			}else{
				printf("%2c %4d\n", ch, fq);
			}
		}
			
	}
};

bool msort(myChar &a, myChar &b){
	return a.fq < b.fq;
}

struct Node{
	bool sign; 	// ���k��0 ������1 (�άۤ�) 
	char ch;	// �`�I�W�� 
	Node *left, *right;
	Node(bool s, char c){
		sign = s;
		ch = c;
		left = nullptr;
		right = nullptr;
	}
	Node(Node *l, Node *r){
		sign = 0;
		ch = 0x01; 	// �D���`�I (���l��) 
		left = l;
		right = r;
	}
	void set(int s){
		sign = s;
	}
	bool DFS(Node *root, char c){
		if(root == nullptr){	// �ǤJroot���p 
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
				if(root->sign){		 // code�[�J�����`�Isign 
					code += "1";
				}else{
					code += "0";
				}
				return true;
			}else return false;
		}else if(root->ch == 0x01){
			if(DFS(root->right, c)){ // �T�w����r���b�k�� 
				if(root->sign){
					code += "1";
				}else{
					code += "0";
				}
				return true;
			}else if(DFS(root->left, c)){ // �T�w����r���b����  
				if(root->sign){
					code += "1";
				}else{
					code += "0";
				}
				return true;
			}
		}
		return false;	// �䤣�� 
	}
	void search(char c){
		int i = 0;
		if(!DFS(nullptr, c)){
			cout << "Error: cant find " << c;
		}
	}
};

void showstate(myChar m[100]){
	for(int i = 0; i < 100; i++){
		if(m[i].fq > 0){
			if(m[i].ch == 0x20){
				printf("\\s %5d\n", m[i].fq);
			}else if(m[i].ch == 0x0A){
				printf("\\n %5d\n", m[i].fq);
			}else if(m[i].ch == 0x01){
				printf("nd %5d\n", m[i].fq);
			}else if(m[i].ch != 0x0D){
				printf("%2c %5d\n", m[i].ch, m[i].fq);
			}
		}
	}
}

void press(char *p ,char *out, Node *root){
	fstream filep, fileout;
	filep.open(p, ios::in);
	fileout.open(out, ios::app);
	if (!filep) {
        std::cerr << "FileP could not be opened!" << std::endl;
    }else if(!fileout){
    	std::cerr << "FileOUT could not be opened!" << std::endl;
	}
	fileout << '\n'; // �Τ���P���Y���} 
	
	
	unsigned int int32 = 0, i = 31;
	char cur;
	while(filep.get(cur)){
		code.clear();
		root->search(cur);
		for(int j = code.size()-1; j >= 0; j--){ // code�|�ϹL�� 
			if(code[j] == '1'){
				int32 = int32 | 0x00000001; // �N bit �g�J 
			}
			if(i != 0){
				int32 = int32 << 1; // 32�줸���g�� �k�� 
				i--;
			}else{
				fileout << int32 << " "; // 32�줸�g�� �H�Ů���}  
				int32 = 0;
				i = 31;
			}
		}
	}
	if(i < 31){
		int32 = int32 << i;	// 32�줸���g�� �k���ɥ�int 
		fileout << int32 << " ";
	}
	
    filep.close();
	fileout.close();
}

int main(){
	
	time_t start = clock();
	char *p = pr, *out = ot;
	
	// show all txt in hex and char
	readfile(p, 1);
	
	// reconstruct char and add fq
	myChar M[100], n[100];
	int k = 0;
	for(int i = 0; i < 200; i++){
		if(fq[i] != 0 && i != 0x0D){ 	// �����n���r 
			M[k++].set(i, fq[i]); 		// �]�w 
		}
	}
	
	// save copy 
	for(int i = 0; i < 100; i++){
		n[i].set(M[i].ch, M[i].fq);
	}
	sort(n, n+100, msort);
	showstate(n);
	
	// construct Huffman
	Node *root, *leave1, *leave0;  			// �ڡB���l��B�k�l�� 
	queue<Node*> Q;							// �w�s�b����� 
	while(M[99].ch != 0x01 || Q.size() != 1){
		sort(M, M+100, msort);				// ���s�ƦC �X�{���ƶ��� 
		for(int i = 0; i < 100; i++){
			if(M[i].fq > 0 && i != 99){	
				if(M[i].ch != 0x01){		// �̤֪��r�� ������ 
					leave1 = new Node(1, M[i].ch);
				}else{
					if(Q.empty()){
						printf("Error: Q is empty");
						return 1;
					} 
					Q.front()->set(1);		//  �Onode, sign���]1 
					leave1 = Q.front();
					Q.pop();
				}
				if(M[i+1].ch != 0x01){		// �ĤG�֦r�� ������
					leave0 = new Node(0, M[i+1].ch);
				}else{
					if(Q.empty()){
						printf("Error: Q is empty");
						return 1;
					} 
					Q.front()->set(0);		// �Onode, sign�k�]0 
					leave0 = Q.front();
					Q.pop();
				}
				root = new Node(leave1, leave0);
				Q.push(root);				// node�ئn ��queue�ƥ� 
				M[i+1].leave(M[i+1].fq + M[i].fq); 	// �X�� 
				M[i].leave(0);						// ���Ƴ]0 (�ư�) 
				break;
			}
		}
	}
	cout << endl;
	
	// init press file
	clearfile(out); 
	writeINT(out, file_size(p));  // (char *filePath, int n)
	
	// show new Huffman code
	for(int i = 0; i < 100; i++){
		if(n[i].fq > 0){
			code.clear();
			Q.front()->search(n[i].ch);  	// �ѤU��queue�N�Oroot 
			reverse(code.begin(), code.end());	// �]���G�ѤU���W��r �G�n�ϹL�� 
			writefile(out, n[i].ch, code);		// �g�J�ɮ׼��Y �U�ۤ��s�X�� 
			
			cout << " " << code << " ";
			if(n[i].ch == 0x0A){
				printf("'\\n'");
			}else if(n[i].ch == 0x20){
				printf("'\\s'");
			}else{
				printf("'%c'", n[i].ch);
			}
			cout << endl;
		}
	}
	
	// press
	press(p ,out, Q.front());
	
	
	
	
    // show cost
    cout << endl << "# file size " << file_size(p) << endl;
	cout << "# Spend time " << clock()-start << "ms" << endl;
	return 0;
} 














