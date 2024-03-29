#include <conio.h>
#include <stdio.h>

#include "quizpages.h"

/**
 * Starts the quiz game loop.
 */
void startGame(int questions) {
    helpPage();

    int topicIndex = topicPage();
    int difficultyIndex = difficultyPage();
    int total = 0, correct = 0, questionsDone[5];

    for (int i = 0; i < questions; i++) {
        qu_Question *question =
            qu_getRandomQuestion(categories[topicIndex], difficulties[difficultyIndex], total, questionsDone);

        int choice = questionPage(question, i + 1, questions);
        if (answerPage(question, choice)) correct++;

        questionsDone[i] = question->questionIndex;
        total++;
        free(question);
    }

    resultPage(total, correct);
}

int main(int argc, char *argv[]) {
    // The default number of questions to be asked per game, can be modified via
    // command line arguments.
    int questions = 5;

    if (argc > 1) questions = atoi(argv[1]);

    while (1) {
        char selected = homePage();
        switch (selected) {
            case 'S':
                startGame(questions);
                break;
            case 'H':
                helpPage();
                break;
        }

        // Keep the option Q outside the switch statement to break the loop when Q is
        // selected rather than breaking just the switch statement.
        if (selected == 'Q') {
            clrscr();
            break;
        }
    }

    return 0;
}
