
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Structure to represent complex numbers
typedef struct
{
    double real;
    double imaginary;
} ComplexNumber;

// Structure to represent a quantum qubit`
typedef struct QubitNode
{
    ComplexNumber alpha;
    ComplexNumber beta;
    struct QubitNode *next;
} QubitNode;

// Function to initialize a quantum qubit
QubitNode *initializeQubit()
{
    QubitNode *qubit = (QubitNode *)malloc(sizeof(QubitNode));
    qubit->alpha.real = 1.0;
    qubit->alpha.imaginary = 0.0;
    qubit->beta.real = 0.0;
    qubit->beta.imaginary = 0.0;
    qubit->next = NULL;
    return qubit;
}

// Function to apply Hadamard gate to a quantum qubit
void applyHadamard(QubitNode *qubit)
{
    ComplexNumber new_alpha, new_beta;

    // Hadamard gate transformation
    new_alpha.real = (1 / sqrt(2)) * (qubit->alpha.real + qubit->beta.real);
    new_alpha.imaginary = (1 / sqrt(2)) * (qubit->alpha.imaginary + qubit->beta.imaginary);

    new_beta.real = (1 / sqrt(2)) * (qubit->alpha.real - qubit->beta.real);
    new_beta.imaginary = (1 / sqrt(2)) * (qubit->alpha.imaginary - qubit->beta.imaginary);

    // Update qubit's state
    qubit->alpha = new_alpha;
    qubit->beta = new_beta;
}

// Function to entangle two quantum qubits
void entangleQubits(QubitNode *qubit1, QubitNode *qubit2)
{
    // Simulating entanglement by making qubits identical
    qubit2->alpha = qubit1->alpha;
    qubit2->beta = qubit1->beta;
}

// Function to display the states of quantum qubits
void displayQubits(QubitNode *qubit)
{
    QubitNode *currentQubit = qubit;
    while (currentQubit != NULL)
    {
        printf("|0⟩ Coefficient: %.2f + %.2fi\n", currentQubit->alpha.real, currentQubit->alpha.imaginary);
        printf("|1⟩ Coefficient: %.2f + %.2fi\n", currentQubit->beta.real, currentQubit->beta.imaginary);
        printf("\n");
        currentQubit = currentQubit->next;
    }
}

// Function to free the memory allocated for quantum qubits
void freeQubits(QubitNode *qubit)
{
    QubitNode *current = qubit;
    QubitNode *next;

    // Free memory for each qubit node
    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
}

// Main function to execute the Quantum Computing Simulator
int main()
{
    int numQubits;
    printf("Enter the number of qubits: ");
    scanf("%d", &numQubits);

    // Initialize qubits
    QubitNode *qubitList = initializeQubit();
    QubitNode *currentQubit = qubitList;

    // Initialize additional qubits
    for (int i = 1; i < numQubits; i++)
    {
        currentQubit->next = initializeQubit();
        currentQubit = currentQubit->next;
    }

    int choice;
    do
    {
        printf("\nQuantum Computing Simulator Menu:\n");
        printf("1. Apply Hadamard Gate (Superposition)\n");
        printf("2. Entangle Qubits\n");
        printf("3. Display Qubit States\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            // Apply Hadamard Gate (Superposition)
            currentQubit = qubitList;
            while (currentQubit != NULL)
            {
                applyHadamard(currentQubit);
                currentQubit = currentQubit->next;
            }
            printf("Hadamard Gate Applied. Qubits in Superposition.\n");
            break;

        case 2:
            // Entangle Qubits
            if (numQubits >= 2)
            {
                entangleQubits(qubitList, qubitList->next);
                printf("Qubits Entangled.\n");
            }
            else
            {
                printf("Entanglement requires at least two qubits.\n");
            }
            break;

        case 3:
            // Display Qubit States
            displayQubits(qubitList);
            break;

        case 4:
            // Exit
            printf("Exiting Quantum Computing Simulator.\n");
            break;

        default:
            // Invalid choice
            printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 4);

    // Free memory
    freeQubits(qubitList);

    return 0;
}
