#include <iostream>

#include <fstream>



using namespace std;



#define HASHTABLE_SIZE 100



typedef struct node

{

    string word;

    string definition;

    struct node* next;

}node;

node** hashtable;
node** hashtable1;



int size = 1, times = 0;

string keyword;



int hash_it(string);

void Load_to_hash();

void Find_Output();



int main(int argc, char* argv[])

{    

    Load_to_hash();

    keyword = argv[1];

    Find_Output();

}

int hash_it(string  needs_hashing)

{

    unsigned int hash = 0;

    for (int i = 0, n = needs_hashing.size(); i < n; i++)

        hash = (hash << 2) ^ needs_hashing[i];

    return hash % HASHTABLE_SIZE * size;

}

void Load_to_hash()

{

    ifstream f("kek.txt");
    ifstream g("kek.txt");
	
    int exit = 0;

    while(true)

    {

        hashtable = new node*[HASHTABLE_SIZE * size];
		hashtable1 = new node*[HASHTABLE_SIZE * size];
      

          while (true)

    {

        node* new_node = new node;
        node* new_node1 = new node;

        getline(f,new_node->word, ';');
        getline(f,new_node->definition, '\n');
        
  
		getline(g,new_node1->definition, ';');
		getline(g,new_node1->word, '\n');

        

        if ( times == HASHTABLE_SIZE * 0.8 * size )

        {

            size *= 2;

            break;
            

        }

        if (f.eof())

        {

            exit = 1;

            break;

        }

        new_node->next = NULL;
        new_node1->next = NULL;

        int h = hash_it(new_node->word);
        int h1 = hash_it(new_node1->word);

        node* head = hashtable[h];
        node* head1 = hashtable1[h1];

        if (head == NULL) hashtable[h] = new_node;

        else

        {

            new_node->next = hashtable[h];

            hashtable[h] = new_node;

        }
        
        if (head1 == NULL) hashtable1[h1] = new_node1;

       else
	   {
    	new_node1->next = hashtable1[h1];
    	hashtable1[h1] = new_node1;
		}
        times++;

    }

    times = 0;

    if (exit == 1) break;

    else delete [] hashtable; delete [] hashtable1;

    

    }
	
    f.close();
    g.close();

}



void Find_Output()

{

      int h = hash_it(keyword);
      int h1 = hash_it(keyword);

    node* cursor = hashtable[h];
    node* cursor1 = hashtable1[h1];

    while (cursor != NULL)

    {

        if (keyword.compare(cursor->word) == 0)

        {

            cout << (cursor->definition);

            break;

        }

        else cursor = cursor->next;
    }
     while (cursor1 != NULL)

    {

        if (keyword.compare(cursor1->word) == 0)

        {

            cout << (cursor1->definition);

            break;

       }

        else cursor1 = cursor1->next;
    }
   cout << endl;
}
