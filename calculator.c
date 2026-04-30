#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#define BUFFER_SIZE 128
#define NUMBER_BUFFER 32
#define DECIMAL_AMOUNT 10000
#define EQUAL_SEPARATOR "================="
#define MINUS_SEPARATOR "-----------------"

double add(const double x, const double y) {
    return x + y;
}

double subtract(const double x, const double y) {
    return x - y;
}

double multiply(const double x, const double y) {
    return x * y;
}

double divide(const double x, const double y) {
    return x / y;
}

double whole_division(double const x, const double y) {
    return round(x) / (int)round(y);
}

int leftover(const double x, const double y) {
    return (int)round(x) % (int)round(y);
}

double power(const double x, const double y) {
    return pow(x, y);
}

double square_root(const double x) {
    return sqrt(x);
}

void print_result(const double x, const double y, const char op, const double answer) {

    if (op == 'r') {
        printf("The value of %.4lf r is %.4lf\n", pow(answer, 2), answer);
    }
    else {
        printf("The value of %.4lf %c %.4lf is %.4lf\n", x, op, y, answer);
    }
}

void print_calc_intro(const double last_answer) {
    printf("%s\n", MINUS_SEPARATOR);
    printf("Division by zero is not permitted! Return value will be NAN!\n");
    printf("Square root will be taken of the absolute value of the entered number.\n");
    printf("The last answer was %.4lf\n", last_answer);
    printf("%s\n", MINUS_SEPARATOR);
}

void handle_zero_division(double *answer) {
    printf("Cannot divide by 0! Result is NAN.\n");
    *answer = 0.0;
}

double get_number(const int *times_used, const double *last_answer) {
    int times_tried = 0;
    char buffer[BUFFER_SIZE], *endprt;
    bool is_valid = false;
    double number = NAN;

    do {
        if (times_tried == 0) {
                printf("Enter a number: ");
        }
        else {
            printf("Wrong input! Value must be a double! Try again: ");
        }

        times_tried++;

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) continue;
        buffer[strcspn(buffer, "\n")] = '\0';

        if (times_used > 0 && strcmp(buffer, "a") == 0) {
            number = *last_answer;
            is_valid = true;
        }
        else {
            number = strtod(buffer, &endprt);

            if (endprt != buffer && *endprt == '\0') {
                is_valid = true;
            }
            else {
                is_valid = false;
            }
        }

    } while (!is_valid);
    printf("%s\n", MINUS_SEPARATOR);

    return number;
}

char get_operator() {
    char buffer[BUFFER_SIZE], operation;
    int times_tried = 0;
    bool is_valid;

    do {
        switch (times_tried) {

            case 0:
                // +, -, *, /, %, w (whole division), p (pow), r (sqrt)
                printf("Enter the operator (type ? for help): ");
                break;

            case -1:
                printf("Enter a operator: ");
                break;

            default:
                printf("Wrong input! Value must be a character! Try again: ");
        }

        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        if (sscanf(buffer, "%c", &operation) == 1) {
            if (strlen(buffer) == 1 && (
                buffer[0] == '+' ||
                buffer[0] == '-' ||
                buffer[0] == '*' ||
                buffer[0] == '/' ||
                (buffer[0] == 'w') ||
                buffer[0] == '%' ||
                buffer[0] == 'p' ||
                buffer[0] == 'r' ||
                buffer[0] == 'h'))
                {
                    is_valid = true;
            }
            else if (strlen(buffer) == 1 && buffer[0] == '?') {
                printf("\n===== List of operations =====\n");
                printf("+ - addition\n");
                printf("- - subtraction\n");
                printf("* - multiplication\n");
                printf("/ - division\n");
                printf("w - integer division\n");
                printf("%% - remainder / modulo\n");
                printf("p - exponentiation (x ^ y)\n");
                printf("r - square root (x || y)\n%s\n", MINUS_SEPARATOR);

                times_tried = -2;
                is_valid = false;
            }

            else {
                is_valid = false;
            }
        }
        else {
            is_valid = false;
        }

        times_tried++;
    } while (!is_valid);
    printf("%s\n", MINUS_SEPARATOR);

    return operation;
}

char get_command() {
    char buffer[BUFFER_SIZE], command;
    int times_tried = 0;
    bool is_valid;

    do {
        switch (times_tried) {

            case 0:
                printf("Enter a command (type ? for help): ");
                break;

            case -1:
                printf("Enter a command: ");
                break;

            default:
                printf("Wrong input! Value must be a character! Try again: ");
        }

        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        if (sscanf(buffer, "%c", &command) == 1) {
            if (strlen(buffer) == 1 && (
                buffer[0] == 'c' ||
                buffer[0] == 'h' ||
                buffer[0] == 'q' ||
                buffer[0] == 'p' ||
                buffer[0] == 'r' ))
            {
                is_valid = true;
            }
            else if (strlen(buffer) == 1 && buffer[0] == '?') {
                printf("\n===== List of commands =====\n");
                printf("c - clear window\n");
                printf("h - show last answer\n");
                printf("q - exit calculator\n");
                printf("p - proceed to the calculator\n");
                printf("r - resets the calculator information\n%s\n", MINUS_SEPARATOR);

                times_tried = -2;
                is_valid = false;
            }

            else {
                is_valid = false;
            }
        }
        else {
            is_valid = false;
        }

        times_tried++;
    } while (!is_valid);

    return command;
}

char get_root() {
    char buffer[BUFFER_SIZE], character;
    int times_tried = 0;
    bool is_valid;

    do {
        if (times_tried == 0) {
                printf("Do you want to do the square root of x or the square root of y? (x/y) :");
        }
        else {
            printf("Wrong input! Value must be x or y! Try again: ");
        }

        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        if (sscanf(buffer, "%c", &character) == 1) {
            if (strlen(buffer) == 1 && (buffer[0] == 'x' || buffer[0] == 'y'))
            {
                is_valid = true;
            }
            else {
                is_valid = false;
            }
        }
        else {
            is_valid = false;
        }

        times_tried++;
    } while (!is_valid);
    printf("%s\n", MINUS_SEPARATOR);

    return character;
}

double calculator(const double last_answer, const int times_used) {

    // all the variables we will need
    double answer = 0;
    char root;

    print_calc_intro(last_answer);

    const double x = get_number(&times_used, &last_answer);
    const char operation = get_operator();
    const double y = get_number(&times_used, &last_answer);

    // seeing witch operation we will use
    switch (operation) {

        case '+':
            answer = round(add(x, y) * DECIMAL_AMOUNT) / DECIMAL_AMOUNT;
            print_result(x, y, operation, answer);
            break;

        case '-':
            answer = round(subtract(x, y) * DECIMAL_AMOUNT) / DECIMAL_AMOUNT;
            print_result(x, y, operation, answer);
            break;

        case '*':
            answer = round(multiply(x, y) * DECIMAL_AMOUNT) / DECIMAL_AMOUNT;
            print_result(x, y, operation, answer);
            break;

        case '/':
            if (y == 0) {
                handle_zero_division(&answer);
            }
            else {
                answer = round(divide(x, y) * DECIMAL_AMOUNT) / DECIMAL_AMOUNT;
                print_result(x, y, operation, answer);
            }

            break;

        case 'w':
            if (y == 0) {
                handle_zero_division(&answer);
            }
            else {
                answer = whole_division(x, y);
                print_result(x, y, operation, answer);
            }

            break;

        case '%':
            if (y == 0) {
                handle_zero_division(&answer);
            }
            else {
                answer = (double)leftover(x, y);
                print_result(x, y, operation, answer);
            }

            break;

        case 'p':
            answer = round(power(x, y) * DECIMAL_AMOUNT) / DECIMAL_AMOUNT;
            print_result(x, y, operation, answer);
            break;

        case 'r':
            root = get_root();

            switch (root) {
                case 'x':
                    answer = round(square_root(fabs(x)) * DECIMAL_AMOUNT) / DECIMAL_AMOUNT;
                    break;

                case 'y':
                    answer = round(square_root(fabs(y)) * DECIMAL_AMOUNT) / DECIMAL_AMOUNT;
                    break;

                default:
                    printf("Unrecognized variable!\n");
                    break;
            }

            print_result(x, y, operation, answer);

            break;

        default: {
            printf("Unrecognized operation!\n");
            break;
        }
    }
    printf("%s\n", EQUAL_SEPARATOR);

    return answer;
}

// main func
int main() {
    double last_answer = NAN, answer = NAN;
    int times_used = 0;
    bool running = true;

    printf("\n%s WELCOME TO THE CALCULATOR %s\n", EQUAL_SEPARATOR, EQUAL_SEPARATOR);

    while (running) {

        const char command = get_command();

        switch (command) {

            case 'c':
                system(CLEAR);
                break;

            case 'h':
                printf("The last answer was %.4lf\n", last_answer);
                break;

            case 'p':
                last_answer = answer;
                answer = calculator(last_answer, times_used);
                times_used++;
                break;

            case 'q':
                printf("\n%s\nBye!\n%s\n", EQUAL_SEPARATOR, EQUAL_SEPARATOR);
                running = false;
                break;

            case 'r':
                last_answer = 0;
                answer = 0;
                break;

            default:
                printf("Unrecognized command!");
                break;
        }
    }
}