#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

// Function to evaluate a simple expression with operators +, -, *, /
double evaluate(double* terms, char* operators, int num_terms) {
    double result = terms[0];
    
    for (int i = 0; i < num_terms - 1; i++) {
        switch (operators[i]) {
            case '+':
                result += terms[i + 1];
                break;
            case '-':
                result -= terms[i + 1];
                break;
            case '*':
                result *= terms[i + 1];
                break;
            case '/':
                // Avoid division by zero
                if (terms[i + 1] == 0) {
                    return -999999; // Error value
                }
                result /= terms[i + 1];
                break;
        }
    }
    
    return result;
}

// Function to generate random terms and operators
bool generate_equation(double target, int num_terms, double epsilon) {
    double* terms = (double*)malloc(num_terms * sizeof(double));
    char* operators = (char*)malloc((num_terms - 1) * sizeof(char));
    char op_choices[] = {'+', '-', '*', '/'};
    
    int max_attempts = 10000;
    int attempts = 0;
    
    while (attempts < max_attempts) {
        attempts++;
        
        // Generate random terms (between 1 and 20)
        for (int i = 0; i < num_terms; i++) {
            terms[i] = (rand() % 20) + 1;
        }
        
        // Generate random operators
        for (int i = 0; i < num_terms - 1; i++) {
            operators[i] = op_choices[rand() % 4];
        }
        
        // Evaluate the expression
        double result = evaluate(terms, operators, num_terms);
        
        // Check if the result matches the target with some tolerance
        if (result != -999999 && fabs(result - target) < epsilon) {
            // Success! Print the equation
            printf("%g", terms[0]);
            for (int i = 0; i < num_terms - 1; i++) {
                printf(" %c %g", operators[i], terms[i + 1]);
            }
            printf(" = %g\n", target);
            
            free(terms);
            free(operators);
            return true;
        }
    }
    
    printf("Could not find a matching equation after %d attempts.\n", max_attempts);
    free(terms);
    free(operators);
    return false;
}

int main() {
    double target;
    int num_terms;
    int num_equations;
    srand(time(NULL)); // Seed random number generator
    
    printf("Reverse Calculator\n");
    printf("------------------\n");
    printf("Enter the target number: ");
    scanf("%lf", &target);
    
    printf("Enter the number of terms to use (2-5): ");
    scanf("%d", &num_terms);
    
    // Validate input
    if (num_terms < 2 || num_terms > 5) {
        printf("Number of terms must be between 2 and 5.\n");
        return 1;
    }
    
    printf("How many equations would you like to generate? ");
    scanf("%d", &num_equations);
    
    printf("\nGenerating %d equation(s) for target number %g with %d terms...\n\n", 
           num_equations, target, num_terms);
    
    // Set a small epsilon for floating-point comparison
    double epsilon = 0.0001;
    
    int found = 0;
    for (int i = 0; i < num_equations; i++) {
        if (generate_equation(target, num_terms, epsilon)) {
            found++;
        }
    }
    
    printf("\nFound %d equation(s) matching the target value.\n", found);
    
    return 0;
}
