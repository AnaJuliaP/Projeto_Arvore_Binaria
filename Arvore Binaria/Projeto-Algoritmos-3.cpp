#include <iostream>
#include <list>
#include <cstring>
#include <locale.h>
using namespace std;

struct Item
{
	char nome[100];
	char pMagica[100]; //propriedade magica
	int id; //identificacao
	char forca[100]; //forca de forca (“Fraco”, “Moderado” e “Excelente”)
};

struct treenode
{
	Item item;
	treenode *esq;
	treenode *dir;

};
typedef treenode *treenodeptr;

//Insere em ordem alfabetica
void tInsere(treenodeptr &p, Item x, string tipo)
{
	if (p == NULL) // insere na raiz
	{
		p = new treenode;
		p->item = x;
		p->esq = NULL;
		p->dir = NULL;
	}
	else if(tipo == "nome")
	{
		if (strcmp(x.nome, p->item.nome) < 0)// insere na subarvore esquerda
			tInsere(p->esq, x, "nome");
		else // insere na subarvore direita
			tInsere(p->dir, x, "nome");
	}
	else if(tipo == "propriedade")
	{
		if (strcmp(x.pMagica, p->item.pMagica) < 0)// insere na subarvore esquerda
			tInsere(p->esq, x, "propriedade");
		else // insere na subarvore direita
			tInsere(p->dir, x, "propriedade");
	}
	else if(tipo == "forca")
	{
		if ((strcmp(x.forca, "Fraco") == 0) || ((strcmp(x.forca, "Moderado") == 0) && (strcmp(p->item.forca, "Excelente") == 0))) // insere na subarvore esquerda
			tInsere(p->esq, x, "forca");
		else // insere na subarvore direita
			tInsere(p->dir, x, "forca");
	}
}

//Pesquisar item por nome
treenodeptr tPesq(treenodeptr p, char nome[])
{
	if (p == NULL) // elemento nao encontrado
		return NULL;
	else if (strcmp(nome, p->item.nome) == 0) // elemento encontrado na raiz
		return p;
	else if (strcmp(nome, p->item.nome) < 0) // procura na subarvore esquerda
		return tPesq(p->esq, nome);
	else // procura na subarvore direita
		return tPesq(p->dir, nome);
}

void tDestruir (treenodeptr &arvore)
{
	if (arvore != NULL)
	{
		tDestruir(arvore->esq);
		tDestruir(arvore->dir);
		delete arvore;
	}
	arvore = NULL;
}

treenodeptr tMenor(treenodeptr &raiz)
{
	treenodeptr t;
	t = raiz;
	if (t->esq == NULL) // encontrou o menor valor
	{
		raiz = raiz->dir;
		return t;
	}
	else // continua a busca na sub-arvore esquerda
		return tMenor(raiz->esq);
}

int tRemove(treenodeptr &raiz, Item x)
{
	treenodeptr p;
	if (raiz == NULL) // ?arvore vazia
		return 1;
	if (strcmp(x.nome, raiz->item.nome) == 0)
	{
		p = raiz;
		if (raiz->esq == NULL) // a raiz não tem filho esquerdo
			raiz = raiz->dir;
		else
		{
			if (raiz->dir == NULL) // a raiz n~ao tem filho direito
				raiz = raiz->esq;
			else // a raiz tem ambos os filhos
			{
				p = tMenor(raiz->dir);
				raiz->item = p->item;
			}
		}
		delete p;
		return 0;
	}
	else if (strcmp(x.nome, raiz->item.nome) < 0)
		return tRemove(raiz->esq, x);
	else
		return tRemove(raiz->dir, x);
}

void removeEmNivel(treenodeptr t, int nivel)
{
	treenodeptr n;
	list<treenodeptr> q;
	int prof; //profundidade da arvore
	prof = 0;
	if (t != NULL)
	{
		q.push_back(t);
		while (!q.empty())
		{
			int tamanho = q.size();
			for(int i = 0; i < tamanho; i++)
			{
				n = *q.begin();
				if(prof == nivel)
					tRemove(t, n->item);
				q.pop_front();
				if (n->esq != NULL)
					q.push_back(n->esq);
				if (n->dir != NULL)
					q.push_back(n->dir);
			}
			prof++;
		}
	}
}

void posOrdem (char y[], treenodeptr arvore, int pos, int &pos2)
{
	if (arvore != NULL)
	{
		posOrdem(y, arvore->esq, pos, pos2);
		posOrdem(y, arvore->dir, pos, pos2);
		pos++;
		if(strcmp(y, arvore->item.nome) == 0)
		{
			pos2 = pos;
		}
	}
}

void preOrdem (char y[], treenodeptr arvore, int pre, int &pre2)
{
	if (arvore != NULL)
	{
		pre++;
		if(strcmp(y, arvore->item.nome) == 0)
			pre2 = pre;
		preOrdem(y, arvore->esq, pre, pre2);
		preOrdem(y, arvore->dir, pre, pre2);
	}
}

void PemOrdem(char y[], treenodeptr arvore, int em, int &em2)
{
	if (arvore != NULL)
	{
		PemOrdem(y, arvore->esq, em, em2);
		em++;
		if(strcmp(y, arvore->item.nome) == 0)
			em2 = em;
		PemOrdem(y, arvore->dir, em, em2);
	}

}

//Mostrar informacoes em ordem crescente
void emOrdem (treenodeptr arvore)
{
	if (arvore != NULL)
	{
		emOrdem(arvore->esq);
		cout << arvore->item.nome << ", ";
		cout << arvore->item.pMagica << ", ";
		cout << arvore->item.id << ", ";
		cout << arvore->item.forca << endl;
		emOrdem(arvore->dir);
	}
}

//Ordenar arvore em ordem de propriedade ou nível
void reordenar(treenodeptr arvore, treenodeptr &arvoreNova, string tipo)
{
	//percorrer arvore inicial em pre ordem
	if (arvore != NULL)
	{
		if(tipo == "propriedade")
		{
			tInsere(arvoreNova, arvore->item, "propriedade");
			reordenar(arvore->esq, arvoreNova, "propriedade");
			reordenar(arvore->dir, arvoreNova, "propriedade");
		}
		else if(tipo == "forca")
		{
			tInsere(arvoreNova, arvore->item, "forca");
			reordenar(arvore->esq, arvoreNova, "forca");
			reordenar(arvore->dir, arvoreNova, "forca");
		}
	}
}

//Quantidade de itens que possuem a mesma propriedade mágica
void quantProp(treenodeptr arvore, string props[], int tam, int quant[])
{
	//Pre ordem para percorrer a árvore
	if (arvore != NULL)
	{
		//Contabilizar cada propriedade mágica
		for(int i = 0; i < tam; i++)
			if(props[i] == arvore->item.pMagica)
				quant[i]++;

		quantProp(arvore->esq, props, tam, quant);
		quantProp(arvore->dir, props, tam, quant);
	}
}

int main()
{
	setlocale(LC_ALL, "portuguese");
	treenodeptr arvore = NULL; // começa com NULL
	treenodeptr arvoreProp = NULL; //arvore em ordem de propriedade
	treenodeptr arvoreForca = NULL; //arvore em ordem de forca
	Item item; // nome item a ser inserido
	int id; //identificação do item
	string *props = NULL; //propiedades mágicas dos itens
	int *quant = NULL; //quantidade de cada propridade mágica
	int nivel; //nivel em que ira remover os itens
	char nomeBuscado[100];
	int em = -1, pos = -1, pre = -1;

	//Ler itens e inserir na arvore por ordem crescente de nome
	cin.getline(item.nome, 100);
	id = 1;
	while(strcmp(item.nome, "0") != 0)
	{
		cin.getline(item.pMagica, 100);
		item.id = id;
		id++;
		cin.getline(item.forca, 100);
		tInsere(arvore, item, "nome");
		cin.getline(item.nome, 100);
	}

	//Mostrar em ordem crescente de nome
	cout << "Itens por ordem crescente de nome:" << endl;
	emOrdem(arvore);
	cout << endl;

	//Ordenar e mostrar propriedades mágicas de forma alfabética
	cout << "Itens por ordem alfabética de propriedades mágicas:" << endl;
	reordenar(arvore, arvoreProp, "propriedade");
	emOrdem(arvoreProp);
	cout << endl;

	//mostrar a pesquisa por nome
	cout << "Entre com o nome a ser buscado:" << endl;
	cin.getline(nomeBuscado, 100);
	if (tPesq(arvore, nomeBuscado) != NULL)
	{
		cout << "Item encontrado!" << endl;
	}
	else
	{
		cout << "Item não encontrado!" << endl;
	}
	cout << endl;

	//Iniciar vetor com propriedades mágicas e quantidade inicial 0
	props = new string[4];
	quant = new int[4];
	props[0] = "Atear fogo";
	props[1] = "Congelar";
	props[2] = "Nenhuma";
	props[3] = "Regenera vida";
	for(int i = 0; i < 4; i++)
		quant[i] = 0;
	//Mostrar quantidade de cada propridade mágica
	quantProp(arvore, props, 4, quant);
	for(int j = 0; j < 4; j++)
		cout << "Há " << quant[j] << " itens com propriedade mágica " << props[j] << endl;
	cout << endl;

	//Ordenar e mostrar nivel de força em ordem crescente
	cout << "Itens por ordem crescente de nível de força:" << endl;
	reordenar(arvore, arvoreForca, "forca");
	emOrdem(arvoreForca);
	cout << endl;

	//Descobrir percurso mais rápido
	cout << "Entre com o nome do item para descobrir o menor percurso:" << endl;
	cin.getline(nomeBuscado, 100);
	PemOrdem(nomeBuscado, arvore, 0, em);
	if (em == -1)
	{
		cout << "Elemento não encontrado" << endl;
	}
	else
	{
		posOrdem(nomeBuscado, arvore, 0, pos);
		preOrdem(nomeBuscado, arvore, 0, pre);

		if ((em <= pos) && (em <= pre))
		{
			cout << "emOrdem" << endl;
		}
		else if (pos <= pre)
		{
			cout << "posOrdem" << endl;
		}
		else
		{
			cout << "preOrdem" << endl;
		}
	}
	cout << endl;

	//Ler nivel, remover elementos dele e mostrar arvore em ordem
	cout << "Entre com o nível que deseja remover os elementos:" << endl;
	cin >> nivel;
	removeEmNivel(arvore, nivel);
	cout << "Itens por ordem crescente de nome com o nível " << nivel << " removido:" << endl;
	emOrdem(arvore);

	//Destruir a arvore
	tDestruir(arvore);
	tDestruir(arvoreProp);
	tDestruir(arvoreForca);

	return 0;
}
