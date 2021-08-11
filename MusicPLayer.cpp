#include<bits/stdc++.h>
using namespace std;
class Node{
    public:
    string song;
    Node *next, *prev;
    Node(string song){
        this->song = song;
        next = NULL;
    }
    Node(){
        this->next = NULL;
    }
} *top, *temp, *top1;
void create(){
    top = NULL;
}
void PrintList(Node*);

// Pusihing into the music player
void AddNodeFile(Node *head, string data){
    while(head->next!=NULL){
        head = head->next;
    }
    head->next = new Node(data);
    head->prev = head;
    head = head->next;
}

// option 10 (AddPlayList)
void AddPlayList(Node *head){
    fstream f1;
    string line;
    f1.open("playlist.txt",ios::in);
    while(!f1.eof()){
        getline(f1,line);
        AddNodeFile(head,line);
    }
    cout << "PlayList Added" << endl;
    f1.close();
}



// Option 9 Sort the list
void Sort(Node * &pointer){
    Node *a = NULL, *b = NULL, *c = NULL, *e = NULL, *temp = NULL;
    while(e!=pointer->next){
        c = a = pointer;
        b = a->next;
        while(a!=e){
            if(a->song == a->song){
                if(a == pointer){
                    temp = b->next;
                    b->next = a;
                    a->next = temp;
                    pointer = b;
                    c = b;
                }else{
                    temp = b->next;
                    b->next = a;
                    a->next = temp;
                    c->next = b;
                    c = b;
                }
            }else{
                c = a;
                a = a->next;
            }
            b = a->next;
            if(b == e){
                e = a;
            }

        }
    }
}

// Option 8 TopElement
void TopElement(){
    if(top==NULL){
        cout << "\n\a\a\a\a#NO last played tracks.\n";
        return;
    }
    cout << "\n=>Last Played Song - "<< top->song << endl;
}

// Option - 7 (Most Recent Song)
void Display(){
    top1 = top;
    if(top1==NULL){
        cout << "\n\a\a\a\a=>NO recently played tracks.\n";
        return;
    }
    cout << "\n\a\a\a\a#Recently played tracks-\n";
    while(top1!=NULL){
        cout << top1->song << endl;
        top1 = top1->next;
    }
}

void Recent(){
    Display();
}

// Pushing the played song
void push(string data){
    if(top==NULL){
        top = new Node(data);
    }else{
        if(top->song != data){
            temp = new Node(data);
            temp->next = top;
            top = temp;
        }
    }
}

//Option 6 (play the song)
void Play(Node *head){
    string s;
    PrintList(head);
    cout<<"\n\a\a\a\aChoose song you wish to play- ";
    cin >> s;
    bool flag = false;
    while(head!=NULL){
        if(head->song == s){
            cout<<"\n\a\a\a\a=>Now Playing......"<<s<<endl;
            flag = true;
            push(s);
            break;
        }else{
            head = head->next;
        }
    }
    if(flag == false){
        cout<<"\n\a\a\a\a#Song Not found"<<endl;
    }

}

// Option - 5 (Search the song)
void Search(Node *head){
    string s;
    cin >> s;
    bool flag = false;
    while(head!=NULL){
        if(head->song == s){
            cout<<"\n\a\a\a\a#Song Found"<<endl;
            flag = true;
            break;
        }else{
            head = head->next;
        }
    }
    if(flag==false){
        cout<<"\n\a\a\a\a#Song Not found"<<endl;
    }
    return;
}

// Option - 4
void CountNodes(Node *head){
    int i = 0;
    while(head!=NULL){
        head = head->next;
        i++;
    }
    cout<<"\nTotal songs-  "<< i-1<<endl;
}

// Option 3 - Printing the Linked List
void PrintList(Node *head){
    cout<<"\nPlaylist Name- ";
    while(head!=NULL){
        cout << head->song << endl;
        head = head->next;
    }
    return;
}


// Delete Song from the TXT File
void DeleteFile(string s){
    fstream f1, f2;
    string line;
    int x = 0;
    f1.open("playlist.txt");
    //ofstream MyFile("temp.txt");
    f2.open("temp.txt", ios::out);

    while(!f1.eof()){
        getline(f1,line);

        if(line != s){
                if ( ! f2.is_open() ) {
                cerr << "open error\n";
                }
            f2 << line << endl;
        }else{
            if(line == s){
                x = 1;
            }
        }
    }
    f1.close();
    f2.close();
    remove("playlist.txt");
    rename("temp.txt","playlist.txt");
    if(x==0){
        cout << "There is no song with name you entered." << endl;
    }else{
        cout << "Song has been deleted." << endl;
    }

}

// Delete by Pos
void DelPos(Node *head, int pos){
    Node *curr = head;
    while(curr!=NULL && pos--){
        curr = curr->next;
    }
    if(curr==NULL)
        return;
    curr->prev->next = curr->next;
    if(curr->next!=NULL)
        curr->next->prev = curr->prev;
    curr->next = NULL;
    curr->prev = NULL;
    DeleteFile(curr->song);
    free(curr);
    cout << "The list is updated" << endl;
    cout << "Use the display function to check" << endl;
}
// Delete By Search
void DelSearch(Node *head){
    string s;
    PrintList(head);
    cout<<"\n\a\a\a\aChoose song you wish to delete- ";
    cin >> s;
    int flag = 0;

    while(head!=NULL){
        if(head->song == s){
            cout<<"\n\a\a\a\a#Song Found"<<endl;
            Node *temp;
            temp = new Node();
            temp = head;
            DeleteFile(temp->song);
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            free(temp);
            flag++;
            break;
        }else{
            head = head->next;
        }
    }
    // Song Not Found
    if(flag==0){
        cout<<"\n\a\a\a\a#Song Not found"<<endl;
    }

}

// Option 2
void DeleteNode(Node * &head){
    int c;
    cout<<"Which type of delete do you want?\n1.By Search\n2.By Position"<<endl;
    cin >> c;

    switch(c){
        case 1 : DelSearch(head);
        break;

        case 2: int pos;
        cout << endl << ("Enter the pos of the song : ");
        cin >> pos;
        DelPos(head,pos);
        break;
    }

}

// Write into the File

void ToFile(string s){
    fstream f1;
    remove("playlist.txt");
    f1.open("playlist.txt", ios::out | ios::app);
    f1 << s << endl;
    f1.close();
}

// Option 1
void AddNode(Node *head){
    string s;
    cout<<"\n\a\a\a\aEnter Song name-  ";
    cin >> s;
    ToFile(s);
    while(head->next!=NULL){
        head = head->next;
    }
    head->next = new Node(s);
    head->next->prev = head;
    return;

}
int main(){
    int choice, location;
    string song;
    Node *start, *hold;
    string playlist;
    cout<<"\t\t\t\a\a\a\a**WELCOME**"<<endl;
    cout<<"\n**please use '_' for space."<<endl;
    cout<<"\n\n\a\a\a\aEnter your playlist name-  ";
    cin >> playlist;
    start = new Node(playlist);
    //getline(cin,start->song);
    hold = start;
    create();
    // Loop Begins

    do{
        cout << endl << "1. Add New Song" << endl;
        cout << "2. Delete Song" << endl;
        cout << "3.Display Entered Playlist" << endl;
        cout << "4.Total Songs" << endl;
        cout << "5. Search Songs" << endl;
        cout << "6. Play Song" << endl;
        cout << "7. Recently Played List" << endl;
        cout << "8. Last Played" << endl;
        cout << "9. Sorted playlist" << endl;
        cout << "10. Add From File" << endl;
        cout << "11. Exit" << endl;
        cout<<("\n\a\a\a\aEnter your choice- ");
        cin >> choice;

        // Choice Selection
        switch(choice){

            case 1: AddNode(start);
            break;

            case 2: DeleteNode(start);
            break;

            case 3: PrintList(start);
            break;

            case 4: CountNodes(hold);
            break;

            case 5: Search(start);
            break;

            case 6: Play(start);
            break;

            case 7: Recent();
            break;

            case 8: TopElement();
            break;

            case 9: Sort(start->next);
                    PrintList(start);
            break;

            case 10: AddPlayList(start);
            break;

            case 11: exit(0);

            default : cout << "Wrong Input" << endl;
            exit(0);
        }
    }while(choice != 11);
}
