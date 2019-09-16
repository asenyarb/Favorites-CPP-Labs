#include <fstream>
#include "Bintree.h"
#include <Windows.h>
using namespace std;
int main() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	KBinTree tree; int x;
	ifstream fi ("in.txt");
	if (fi) {
		while (fi >> x) { tree.Insert(x); cout << x<<" "; }
	}
	cout << endl;
	KTNode* t1 = tree.Task2();
	cout << t1->info << endl;
	stack<KTNode*> s; int c(0); bool bo(false);
	KTNode* t2= tree.Task(tree.fpRoot, c, bo);
	cout << t2->info<<endl;
	system("pause");
	return 0;
}