#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for the node of the adjacency list
typedef struct Node {
    char* city_name; // Name of the city
    int weight;      // Transportation charge
    struct Node* next; // Pointer to the next connected city
} Node;

// Define a structure for the graph
typedef struct {
    int num_vertices; // Number of vertices in the graph
    Node** adj_lists; // Array of adjacency lists
} GraphList;

// Function to create a new graph
GraphList* create_graph_list(int vertices) {
    // Allocate memory for the graph structure
    GraphList* graph = malloc(sizeof(GraphList));
    if (graph == NULL) {
        fprintf(stderr, "Error allocating memory for graph\n");
        return NULL;
    }

    // Initialize the number of vertices in the graph
    graph->num_vertices = vertices;

    // Allocate memory for the array of adjacency lists
    graph->adj_lists = malloc(sizeof(Node*) * vertices);
    if (graph->adj_lists == NULL) {
        fprintf(stderr, "Error allocating memory for adjacency lists\n");
        free(graph);
        return NULL;
    }

    // Initialize each adjacency list as empty
    for (int i = 0; i < vertices; i++) {
        graph->adj_lists[i] = NULL;
    }
    return graph;
}

// Function to add an edge to the graph
int add_edge(GraphList* graph, int src, int dest, int weight, const char* src_city, const char* dest_city) {
    // Check if vertices are valid
    if (src < 0 || src >= graph->num_vertices || dest < 0 || dest >= graph->num_vertices) {
        fprintf(stderr, "Invalid vertices\n");
        return -1;
    }

    // Create a new node for the source city
    Node* new_node_src = malloc(sizeof(Node));
    if (new_node_src == NULL) {
        fprintf(stderr, "Error allocating memory for new node\n");
        return -1;
    }
    new_node_src->city_name = strdup(src_city); // Copy the source city name
    new_node_src->weight = weight; // Set the transportation charge
    new_node_src->next = graph->adj_lists[src]; // Link the new node to the beginning of the adjacency list
    graph->adj_lists[src] = new_node_src; // Update the head of the adjacency list

    // Create a new node for the destination city
    Node* new_node_dest = malloc(sizeof(Node));
    if (new_node_dest == NULL) {
        fprintf(stderr, "Error allocating memory for new node\n");
        free(new_node_src);
        return -1;
    }
    new_node_dest->city_name = strdup(dest_city); // Copy the destination city name
    new_node_dest->weight = weight; // Set the transportation charge
    new_node_dest->next = graph->adj_lists[dest]; // Link the new node to the beginning of the adjacency list
    graph->adj_lists[dest] = new_node_dest; // Update the head of the adjacency list

    return 0;
}

// Function to print the graph
void print_graph_list(GraphList* graph) {
    // Iterate over each vertex
    for (int i = 0; i < graph->num_vertices; i++) {
        Node* temp = graph->adj_lists[i]; // Get the head of the adjacency list for the current vertex
        printf("\nAdjacency list of vertex %d\nhead", i);
        // Iterate over each connected city
        while (temp != NULL) {
            printf(" -> %s (Charge: %d)", temp->city_name, temp->weight); // Print the connected city and its charge
            temp = temp->next; // Move to the next node in the adjacency list
        }
        printf("\n");
    }
}

// Function to free memory allocated for the graph
void free_graph(GraphList* graph) {
    if (graph == NULL) {
        return;
    }

    // Iterate over each adjacency list
    for (int i = 0; i < graph->num_vertices; i++) {
        Node* current = graph->adj_lists[i];
        // Iterate over each node in the adjacency list
        while (current != NULL) {
            Node* next = current->next;
            free(current->city_name); // Free the memory allocated for the city name
            free(current); // Free the memory allocated for the node
            current = next; // Move to the next node
        }
    }

    free(graph->adj_lists); // Free the memory allocated for the array of adjacency lists
    free(graph); // Free the memory allocated for the graph structure
}

int main() {
    // Define the number of vertices in the graph
    int vertices = 4;

    // Create a graph with the specified number of vertices
    GraphList* graph = create_graph_list(vertices);
    if (graph == NULL) {
        fprintf(stderr, "Error creating graph\n");
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
