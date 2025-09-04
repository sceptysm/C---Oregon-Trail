#include <iostream>
#include <string>
#include <ctime>



// Global Variables

int totalMileage, cashLeft, bullets, food, clothing, miscSupplies;
int oxenSpending, foodSpending, ammoSpending, clothingSpending, miscSpending;
int currentTurn;
int userShootingSkill;

// Functions

std::string getUserInput(std::string prompt)
{
    std::string in;

    std::cout << prompt << std::endl;
    std::cin >> in;

    return in;
}

int getIntegerInput(std::string prompt, int min, int max)
{
    int in;

    do {
        std::cout << prompt << std::endl;
        std::cin >> in;
        
    } while (in < min || in > max);

    return in;
}

void evaluate(int suspension)
{
    for (int i = 0; i < suspension; i++) {
        std::cout << "..." << std::endl;
        _sleep(300);
    }
}


// Original Subroutines

void printInstructions() 
{

    // Array of strings to hold the instructions
    std::string instructions[] = {
        "YOU HAD SAVED $900 TO SPEND FOR THE TRIP, AND YOU'VE JUST PAID $200 FOR A WAGON.",
        "YOU WILL NEED TO SPEND THE REST OF YOUR MONEY ON THE FOLLOWING ITEMS:",
        "",
        "     OXEN - YOU CAN SPEND $200-$300 ON YOUR TEAM",
        "            THE MORE YOU SPEND, THE FASTER YOU'LL GO",
        "            BECAUSE YOU'LL HAVE BETTER ANIMALS",
        "     FOOD - THE MORE YOU HAVE, THE LESS CHANCE THERE",
        "            IS OF GETTING SICK",
        "     AMMUNITION - $1 BUYS A BELT OF 50 BULLETS",
        "            YOU WILL NEED BULLETS FOR ATTACKS BY ANIMALS",
        "               AND BANDITS, AND FOR HUNTING FOOD",
        "     CLOTHING - THIS IS ESPECIALLY IMPORTANT FOR THE COLD",
        "               WEATHER YOU WILL ENCOUNTER WHEN CROSSING",
        "               THE MOUNTAINS",
        "     MISCELLANEOUS SUPPLIES - THIS INCLUDES MEDICINE AND",
        "              OTHER THINGS YOU WILL NEED FOR SICKNESS",
        "              AND EMERGENCY REPAIRS",
        "",
        "",
        "YOU CAN SPEND ALL YOUR MONEY BEFORE YOU START YOUR TRIP -",
        "OR YOU CAN SAVE SOME OF YOUR CASH TO SPEND AT FORTS ALONG",
        "THE WAY WHEN YOU RUN LOW. HOWEVER, ITEMS COST MORE AT",
        "THE FORTS. YOU CAN ALSO GO HUNTING ALONG THE WAY TO GET MORE FOOD.",
        "WHENEVER YOU HAVE TO USE YOUR TRUSTY RIFLE ALONG THE WAY,",
        "YOU WILL BE TOLD TO TYPE IN THAT WORD (ONE THAT SOUNDS LIKE A",
        "GUN SHOT). THE FASTER YOU TYPE IN THAT WORD AND HIT THE \"ENTER\" KEY, THE BETTER LUCK YOU'LL HAVE WITH YOUR GUN.",
        "AT EACH TURN, ALL ITEMS ARE SHOWN IN DOLLAR AMOUNTS EXCEPT BULLETS",
        "WHEN ASKED TO ENTER MONEY AMOUNTS, DON'T USE A \"$\".",
        "",
        "GOOD LUCK!!!",
        "",
        "",
        "",

    };

    for (const auto &line : instructions) {
        // auto is used to automatically deduce the type of 'line'
        std::cout << line << std::endl;
    }
}

void randomizeShooting(int level) 
{
    std::string response;
    std::string shootWord;
    
    int timeTaken;
    double startTime;

    int randNum = rand() % 3;

    std::string words[] = {
        "BANG",
        "BLAM",
        "POW",
        "WHAM"
    };


    shootWord = words[randNum];
    
    std::cout << "TYPE '" << shootWord << "'" << std::endl;

    startTime = static_cast<double>(clock()) / CLOCKS_PER_SEC;

    std::cin >> response;

    timeTaken = static_cast<int>((static_cast<double>(clock()) / CLOCKS_PER_SEC - startTime) * 1000);

    evaluate(3);
    //@TODO: FINISH TIME CHECK


    if (response == shootWord)
    {
        std::cout << "NICE SHOT!" << std::endl;
    }
    else
    {
        std::cout << "YOU MISSED!" << std::endl;
    }
}

void illnessRoutine(int eatingChoice,int miscSupplies, int blizzardFlag) 
{

    //@TODO : ADD BLIZZARD FLAG CHECK
    
    int random = rand() % 100;
    
    if (random < 10 + 35 * (eatingChoice - 1))
    {
        std::cout << "MILD ILLNESS---MEDICINE USED" << std::endl;
        miscSupplies -= 2;

    }
    else if (random < 60)
    {
        std::cout << "SERIOUS ILLNESS---YOU MUST STOP FOR MEDICAL ATTENTION" << std::endl;
        miscSupplies -= 10;
    }
    else
    {
        std::cout << "BAD ILLNESS---MEDICINE USED";
        miscSupplies -= 5;
    }

    if (miscSupplies < 0)
    {
        std::cout << "YOU RAN OUT OF MEDICAL SUPPLIES AND DIED." << std::endl;
        exit(0);
    }

}

void mainTurn() {

    int choice;

    std::cout << "TOTAL MILEAGE: " << totalMileage << std::endl;
    std::cout << "FOOD: " << food << std::endl;
    std::cout << "BULLETS: " << bullets << std::endl;
    std::cout << "CLOTHING: " << clothing << std::endl;
    std::cout << "MISC. SUPPLIES: " << miscSupplies << std::endl;
    std::cout << "CASH : $" << cashLeft << std::endl;

    std::cout << "DO YOU WANT TO:" << std::endl;
    std::cout << "1. STOP AT A FORT" << std::endl;
    std::cout << "2. HUNT" << std::endl;
    std::cout << "3. CONTINUE" << std::endl;

    choice = getIntegerInput("", 1, 3);


    // @TODO: FINISH CHOICE
    switch (choice) {
        case 1:
        // do fort shit
            break;
        case 2:
            if (bullets >= 40) 
            {
                randomizeShooting(userShootingSkill);
            }
            else 
            {
                evaluate(1);
                std::cout << "TOUGH---YOU NEED MORE BULLETS TO GO HUNTING." << std::endl;
            }
            break;
        case 3:
            totalMileage += 100 + rand() % 50;

            evaluate(3);

            break;

    }

}




int main()
{

    // INIT SETUP

    std::cout << "DO YOU NEED INSTRUCTIONS? (YES/NO)" << std::endl;

    std::string c;
    std::cin >> c;

    if (c == "YES") {
        printInstructions();
    }

    std::cout << "HOW GOOD A SHOT ARE YOU WITH YOUR RIFLE?" << std::endl;
    std::cout << "  (1) ACE MARKSMAN,  (2) GOOD SHOT,  (3) FAIR TO MIDDLIN'" << std::endl;
    std::cout << "  (4) NEED MORE PRACTICE,  (5) SHAKY KNEES" << std::endl;

    userShootingSkill = getIntegerInput("", 1, 5);

    int budget = 700;

    std::cout << "HOW MUCH DO YOU WANT TO SPEND ON YOUR OXEN?" << std::endl;
    std::cout << "YOUR CURRENT BUDGET IS $" << budget << std::endl;
    oxenSpending = getIntegerInput("", 200, 300);
    budget -= oxenSpending;

    std::cout << "HOW MUCH DO YOU WANT TO SPEND ON FOOD?" << std::endl;
    std::cout << "YOUR CURRENT BUDGET IS $" << budget << std::endl;

    foodSpending = getIntegerInput("", 0, budget);
    budget -= foodSpending;

    std::cout << "HOW MUCH DO YOU WANT TO SPEND ON AMMUNITION?" << std::endl;
    std::cout << "YOUR CURRENT BUDGET IS $" << budget << std::endl;

    ammoSpending = getIntegerInput("", 0, budget);
    budget -= ammoSpending;

    std::cout << "HOW MUCH DO YOU WANT TO SPEND ON CLOTHING?" << std::endl;
    std::cout << "YOUR CURRENT BUDGET IS $" << budget << std::endl;

    clothingSpending = getIntegerInput("", 0, budget);
    budget -= clothingSpending;

    std::cout << "HOW MUCH DO YOU WANT TO SPEND ON MISC. SUPPLIES?" << std::endl;
    std::cout << "YOUR CURRENT BUDGET IS $" << budget << std::endl;

    miscSpending = getIntegerInput("", 0, budget);
    budget -= miscSpending;

    cashLeft = budget;

    evaluate(4);

    std::cout << "AFTER ALL YOUR PURCHASES, YOU NOW HAVE $" << cashLeft << " LEFT." << std::endl;


    totalMileage = 0;
    bullets = ammoSpending * 50;
    food = foodSpending;
    clothing = clothingSpending;
    miscSupplies = miscSpending;

    currentTurn = 1;
    while (totalMileage < 2040) 
    {
        std::cout << "TURN " << currentTurn << std::endl;
        mainTurn();
        currentTurn++;
        evaluate(3);

    }


    std::cout << "CONGRATULATIONS! YOU'VE MADE IT TO OREGON CITY!" << std::endl;

    return 0;
}