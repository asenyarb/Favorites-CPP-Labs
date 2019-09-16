#include <iostream>
//#include <list>
#include <queue>
#include <stack>
#ifndef BINTREE_H
#define BINTREE_H
using namespace std;
int maxy(int a, int b) {
	return (a < b) ? b : a;
}
struct KTNode {
	int info;
	KTNode* left, *right;
	KTNode() :info(0), left(0), right(0) {}
	explicit /* не выполнять авт. неявное преобраз */ KTNode(int info, KTNode* left, KTNode* right) :info(info), left(left), right(right) {}
	KTNode(int info) :info(info), left(0), right(0) {}
};
struct node { KTNode *p; int left, right; bool check; };
class KBinTree {
public: KBinTree(): fpRoot(0){}
		bool Insert(int x) {
			bool fbRet = true;
			KTNode **ppPrev = &fpRoot;
			KTNode *p = fpRoot;
			while (p) {
				if (x < p->info) { ppPrev = &p->left; p = p->left; }
				else if (x > p->info) { ppPrev = &p->right; p = p->right; }
				else { fbRet = false; break; }
			}
			if (p == nullptr) { *ppPrev = new KTNode(x); if (fpRoot == 0)fpRoot = *ppPrev; }
			return fbRet;
		}
		KTNode* Find(int x) {
			KTNode *p = fpRoot;
			while (p) {
				if (x < p->info)p = p->left;
				else if (x > p->info)p = p->right;
				else break;
			}
			return p;
		}
		void preOrder(KTNode* p) {
			if (p) {
				cout << p->info << " ";
				preOrder(p->left);
				preOrder(p->right);
			}
		}
		void inOrder(KTNode*p) {
			if (p) {
				inOrder(p->left);
				cout << p->info << " ";
				inOrder(p->right);
			}
		}
		void postOrder(KTNode *p) { 
			if (p) {
				postOrder(p->left);
				postOrder(p->right);
				cout << p->info << " ";
			}
		}
		void OutInpreOrder() {
			preOrder(fpRoot);
		}
		void OutInpostOrder() {
			postOrder(fpRoot);
		}
		void OutIninOrder() {
			inOrder(fpRoot);
		}
		bool IsLeaf(KTNode* t) {
			if ((!t->left) && (!t->right))
				return true;
			else 
				return false;
		}
		KTNode* LIsHigherThanR(KTNode* t, int&h) {
			if (t == nullptr) {
				h = 0;
				return nullptr;
			}
			else 
				if (IsLeaf(t)){
					h = 1;
					return nullptr;
				}
			else {
				int hl, hr;
				KTNode* pl = LIsHigherThanR(t->left,hl);
				KTNode* pr = LIsHigherThanR(t->right, hr);
				if (hl > hr) {
					h = 1 + hl;
					return t;
				}
				if (pl) return pl;
				else return pr;
			}
		}
		KTNode* MaxFull(KTNode*t,bool& b) {//максимальное поддерево с двумя ветками (дерево полное)
			if (t == nullptr) {
				return nullptr;
			}
			else {
				bool isFull_L, isFull_R;
				KTNode* pl = MaxFull(t->left, isFull_L);
				KTNode* pr = MaxFull(t->right,isFull_R);
				if ((isFull_L) && (isFull_R)) {
					b = true;
					return t;
				}
				else {			//t не является полным
					b = false;
					if (pl) 
						return pl;
					else
						return pr;
				}
			}
		}
		KTNode* Task(KTNode* t, int &c, bool&b) {
			if (t == nullptr)return nullptr;
			else if (IsLeaf(t)) {
				c = 1;
				return t;
			}
			else {
				bool bl, br; int cl=0, cr=0;
				auto pl = Task(t->left, cl, bl);
				auto pr = Task(t -> right, cr, br);
				if (bl&&br && (cl > cr)) {
					if (t == fpRoot)return fpRoot;
					c = cl + cr + 1;
					b = true;
					return t;
				}
				else {
					b = false;
					if (cl > cr) {
						c=cl;
						return pl;
					}
					else {
						c=cr;
						return pr;
					}
				}
			}
		}
		int Count(KTNode *t) 
		{
			queue<KTNode*> qu{ {t} };
			int c = 0;
			while(!qu.empty())
			{
				KTNode* q = qu.front();
				qu.pop();
				if (q) {
					++c;
					qu.push(q->left);
					qu.push(q->right);
				}
			}
			return c;
		}
		
		KTNode* Task2()
		{
			pair<KTNode*, int> answer = { nullptr, 0 };
			KTNode *prev = fpRoot, *q = fpRoot;
			stack<node> S; 

			while (true)
			{
				while (q) { S.push({ q, 0, 0, true }); q = q->left; }
				if (S.empty()) break;
				q = S.top().p;
				if (q->right && (q->right != prev))
				{
					q = q->right;
				}
				else
				{
					prev = q; q = 0;
					auto temp = S.top();
					S.pop();
					if (S.empty()) break;

					++temp.left;
					(S.top().p->info > temp.p->info) ? S.top().left += (temp.left + temp.right) : S.top().right += (temp.left + temp.right);
					if (!temp.check) S.top().check = false;
					if ((temp.p->info > S.top().p->info || S.top().p->right == nullptr) && S.top().left <= S.top().right) S.top().check = false;

					if ((temp.p->info > S.top().p->info || S.top().p->right == nullptr) && answer.second < S.top().left + S.top().right && S.top().check)
					{
						answer.second = S.top().left + S.top().right;
						answer.first = S.top().p;
					}

				}
			}
			return answer.first;
		}
	KTNode *fpRoot;
};
#endif