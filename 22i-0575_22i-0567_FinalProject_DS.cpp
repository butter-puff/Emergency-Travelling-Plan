#include <iostream>
using namespace std;

//to solve this question we use a linked list implementation of queue
class Queue {
private:
    struct Node { //defining a Node for the linked list 
        int data;
        Node* next;
        
        Node(int val1) {
        data=val1;
        next=nullptr;
        }
    };

    Node* front; //pointers to the front and the back of the queue
    Node* rear;

public:
    Queue() : front(nullptr), rear(nullptr) {} //constructor for the initalisation of the queue

    void push(int v) { //adds a new node to the rear 
        Node* newN = new Node(v);
        if (rear == nullptr) {
            front = rear = newN;
        } else {
            rear->next = newN;
            rear = newN;
        }
    }

    void pop() { //removes the front node 
        if (front != nullptr) {
            Node* n = front;
            front = front->next;
            if (front == nullptr) {
                rear = nullptr;
            }
            delete n;
        }
    }

    int front_i() { //returns us the element at the front of the queue
        return (front != nullptr) ? front->data : -1;  
    }

    bool empty() { //checking if queue empty or not 
        return (front == nullptr);
    }
};

void adjacency_list(int cities, int graph[100][100]) { //this prints our adjacency list by traversing through each city and its connections and printing the neighbour for each city
    cout << "Adjacency List:" << endl;
    for (int i = 0; i < cities; ++i) {
        cout << "City " << i << ": ";
        for (int j = 0; j < cities; ++j) {
            if (graph[i][j] == 1) {
                cout << j << " ";
            }
        }
        cout << endl;
    }
}

int min_days_calc(int num_C, int** a_routes, int num_R) { //calculating the min days required to travel from source city to destination
   
    int graph[100][100] = {0};  //this is the adjacency matrix, if there is a direct route then graph[100][100]=1

    for (int i = 0; i < num_R; i++) {
        int src = a_routes[i][0];
        int dest = a_routes[i][1];
        graph[src][dest] = 1;
    }

    
    adjacency_list(num_C, graph);

   
    int d[100]; //minimum days required to reach each city
    for (int i = 0; i < num_C; ++i) {
        d[i] = -1; //all set to -1
    }
    d[0] = 0; //except the source city which will be 0

    
    Queue q; //creating a queue for bfs, starting with source city
    q.push(0);  

    while (!q.empty()) {
        int curr_city = q.front_i(); //get the current city from front of queue and remove it
        q.pop();

        for (int associated = 0; associated < num_C; ++associated) { //here we check if there are any direct aerial routes to neigbouring city
            if (graph[curr_city][associated] == 1 && d[associated] == -1) {
                q.push(associated); //if there is a direct route then push the neighbour into the queue
                d[associated] = d[curr_city]; //update the minimum days to reach the neighbor which will be same as current city

                if (associated == num_C - 1) {
                    return d[associated];
                }
            }
        }

        //exploring the possible cities within the next 6 cities 
        for (int i = curr_city + 1; i <= std::min(curr_city + 6, num_C); i++) {
            if (d[i] == -1) {
                q.push(i); //if that city hasnt been visited then we add it to queue
                d[i] = d[curr_city] + 1; //one more day is then added to our calculation

                if (i == num_C - 1) { //if we have reached the destination city which is n-1 then return the distance calculated
                    return d[i];
                }
            }
        }
    }

    return -1;  
}

int main() {
   
    int num_t;
    cout << "Number of test cases:"; //getting the number of cases required
    cin >> num_t;

    for (int i = 1; i <= num_t; ++i) {
        //looping for each test case
        cout << "Test Case " << i << ":" << endl;
	//getting inputs for cities and aerial routes
        int num_c, num_r;
        cout << "Number of cities: " << endl;
        cin >> num_c;

        cout << "Number of aerial routes: " << endl;
        cin >> num_r;
	//dynamically allocating memory for aerial routes so we can store info about multiple aerial routes in a structured way
        int** aerial_r = new int*[num_r];
        for (int i = 0; i < num_r; ++i) {
            aerial_r[i] = new int[2];
            cout << "\nEnter source and destination separated by space:";
            cin >> aerial_r[i][0] >> aerial_r[i][1];
            cout << "Aerial Route " << i + 1 << ": " << aerial_r[i][0] << " to " << aerial_r[i][1] << endl;
        }

        
        int ans = min_days_calc(num_c, aerial_r, num_r); //calling our final function

        
        cout << "Minimum days required: " << ans << endl;

        
        for (int i = 0; i < num_r; ++i) { //deallocating memory to avoid memory leaks
            delete[] aerial_r[i];
        }
        delete[] aerial_r;
    }

    return 0;
}
