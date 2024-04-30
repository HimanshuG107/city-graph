#include <iostream>
#include <vector>
#include <string>

// Define a structure for the node of the adjacency list
struct Node {
    std::string city_name; 
    int weight;            // Transportation charge
    Node* next;            // Pointer to the next connected city
};

// Define a structure for the graph
struct GraphList {
    int num_vertices;         // Number of vertices in the graph
    std::vector<Node*> adj_lists; // Vector of adjacency lists
};

// Function to create a new graph
GraphList* create_graph_list(int vertices) {
    // Allocate memory for the graph structure
    GraphList* graph = new GraphList;
    graph->num_vertices = vertices;

    // Initialize each adjacency list as empty
    graph->adj_lists.resize(vertices, nullptr);
    return graph;
}

// Function to add an edge to the graph
int add_edge(GraphList* graph, int src, int dest, int weight, const std::string& src_city, const std::string& dest_city) {
    // Check if vertices are valid
    if (src < 0 || src >= graph->num_vertices || dest < 0 || dest >= graph->num_vertices) {
        std::cerr << "Invalid vertices\n";
        return -1;
    }

    // Create a new node for the source city
    Node* new_node_src = new Node;
    new_node_src->city_name = src_city;
    new_node_src->weight = weight;
    new_node_src->next = graph->adj_lists[src];
    graph->adj_lists[src] = new_node_src;

    // Create a new node for the destination city
    Node* new_node_dest = new Node;
    new_node_dest->city_name = dest_city;
    new_node_dest->weight = weight;
    new_node_dest->next = graph->adj_lists[dest];
    graph->adj_lists[dest] = new_node_dest;

    return 0;
}

// Function to print the graph
void print_graph_list(GraphList* graph) {
    // Iterate over each vertex
    for (int i = 0; i < graph->num_vertices; i++) {
        Node* temp = graph->adj_lists[i];
        std::cout << "\nAdjacency list of vertex " << i << "\nhead";
        // Iterate over each connected city
        while (temp != nullptr) {
            std::cout << " -> " << temp->city_name << " (Charge: " << temp->weight << ")";
            temp = temp->next;
        }
        std::cout << "\n";
    }
}

// Function to free memory allocated for the graph
void free_graph(GraphList* graph) {
    if (graph == nullptr) {
        return;
    }

    // Iterate over each adjacency list
    for (size_t i = 0; i < graph->adj_lists.size(); i++) {
        Node* current = graph->adj_lists[i];
        // Iterate over each node in the adjacency list
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    // Free the memory allocated for the graph structure
    delete graph;
}

int main() {
    // Define the number of vertices in the graph
    int vertices = 4;

    // Create a graph with the specified number of vertices
    GraphList* graph = create_graph_list(vertices);
    if (graph == nullptr) {
        std::cerr << "Error creating graph\n";
        return 1;
    }

    // Add edges representing roads and their associated transportation charges
    add_edge(graph, 0, 1, 50, "Delhi", "Bangalore");
    add_edge(graph, 0, 2, 30, "Delhi", "Chennai");
    add_edge(graph, 1, 3, 60, "Bangalore", "Kolkata");
    add_edge(graph, 2, 3, 70, "Chennai", "Kolkata");

    // Print the graph
    print_graph_list(graph);

    // Free the memory allocated for the graph
    free_graph(graph);

    return 0;
}
