#include <iostream> 
#include <fstream>	
#include <sstream>
#include <cstring>
#include <vector>
#include <string>	
#include <algorithm>
#include <random>
#include <chrono>
#include <map>

using namespace std; 

class Player; 

class Board{ 
private: 
    friend class Player;   
    friend class Game;  
    struct FieldData {
        Player* Owner; 
        string Name;
        string Type;
        string Color; 
        int Position;
        int Price; 
        int PriceBuild; 
        int Rent; 
        int RentBuild1; 
        int RentBuild2; 
        int RentBuild3; 
        int RentBuild4; 
        int RentBuild5; 
        int Number;
        FieldData* nextField;
    };
    

    
    FieldData* headptr; 
public: 
    

    Board(){ 
        headptr = nullptr; 
    }

    ~Board(){
        FieldData* current = headptr;
        while (current != nullptr){
            FieldData* temp = current; 
            current = current->nextField;
            delete temp;
        }
        
    }
    FieldData* getFirstPosition(void) const{ 
        return headptr;
    }


    FieldData* createField(Player* owner, const string& name, const string& type,
                    const string& color, int position, int price,
                    int priceBuild, int rent, int rentBuild1, int rentBuild2,
                    int rentBuild3, int rentBuild4, int rentBuild5) {
        FieldData* newNode = new FieldData;
        newNode-> Owner= owner; 
        newNode->Name = name;
        newNode->Type = type;
        newNode->Color = color;
        newNode->Position = position;
        newNode->Price = price;
        newNode->PriceBuild = priceBuild;
        newNode->Rent = rent;
        newNode->RentBuild1 = rentBuild1;
        newNode->RentBuild2 = rentBuild2;
        newNode->RentBuild3 = rentBuild3;
        newNode->RentBuild4 = rentBuild4;
        newNode->RentBuild5 = rentBuild5;
        newNode->Number = 0;
        newNode->nextField = nullptr;
        return newNode;
    }

    void appendFiled(const string& name, const string& type,
                        const string& color, int position, int price,
                        int priceBuild, int rent, int rentBuild1, int rentBuild2,
                        int rentBuild3, int rentBuild4, int rentBuild5, int number){
        FieldData* newFieldPtr = createField(nullptr, name, type, color, position, price, 
                                        priceBuild, rent, rentBuild1, rentBuild2,
                                        rentBuild3, rentBuild4, rentBuild5); 
        if (headptr == nullptr) {
            headptr = newFieldPtr;
            headptr->nextField = headptr;
        } 
        else {
            FieldData* current = headptr;
            while (current->nextField != headptr) {
                current = current->nextField;
            }

            current->nextField = newFieldPtr;
            newFieldPtr->nextField = headptr;
        }
    }

    void displayField(ostream& outfile, FieldData* field)const{ 
        outfile << "----------------------------------------" << endl;
        outfile << field->Name << endl;
        outfile << "Type: " << field->Type << endl;
        outfile << "Color: " << field->Color << endl;
        outfile << "Position: " << field->Position << endl;
        outfile << "Price: $" << field->Price << endl;
        outfile << "Price to Build: $" << field->PriceBuild << endl;
        outfile << "Rent: $" << field->Rent << endl;
        outfile << "Rent with 1 House: $" << field->RentBuild1 << endl;
        outfile << "Rent with 2 Houses: $" << field->RentBuild2 << endl;
        outfile << "Rent with 3 Houses: $" << field->RentBuild3 << endl;
        outfile << "Rent with 4 Houses: $" << field->RentBuild4 << endl;
        outfile << "Rent with Hotel: $" << field->RentBuild5 << endl;
        outfile << "Number: " << field->Number << endl;
        outfile << "----------------------------------------" << endl;
    }

     void displayFieldGame(ostream& outfile, FieldData* field)const{ 
        if (field->Color == "None"){ 
            if (field->Type == "Tax"){
                outfile << "You have to pay a";
                if(field->Name == "Luxury Tax"){
                    outfile << " Luxury Tax, which is $" << field->Price << endl; 
                    outfile << "Postion: " << field->Position << endl;  
                }
                else{ 
                    outfile << "n Income Tax, which is $" << field->Price << endl;
                    outfile << "Postion: " << field->Position << endl;
                }
            }
            else if(field->Type == "Chance"){
                outfile << "You are on a chance card field, get one" << endl; 
                outfile << "Postion: " << field->Position << endl;
            }
            else if(field->Type == "Chest"){
                outfile << "You are on a chance card field, get one" << endl;  
                outfile << "Postion: " << field->Position << endl;
            }
            else if(field->Type == "Railroad"){ 
                outfile << "You are on Railroad station: " <<  field->Name << endl; 
                outfile << "Price: $" << field->Price << endl;
                outfile << "There are" << 4 - field->Number <<" left." << endl; 
                outfile << "Postion: " << field->Position << endl;
            }
            else if(field->Type == "Utility"){ 
                outfile << "You are on Utility filed: " <<  field->Name << endl; 
                outfile << "Price: $" << field->Price << " times what you got on dice, if you have one utility object; and 12 times what you got on dice, if you have two utility objects." << endl; 
                outfile << "There are" << 2 - field->Number <<" left." << endl; 
                outfile << "Postion: " << field->Position << endl;
            }
            else if(field->Type == "Jail"){
                outfile << "Free visit to jail, do noyhing." << endl; 
                outfile << "Postion: " << field->Position << endl;
            }
            else if(field->Type == "GoToJail"){
                outfile << "I am sorry, you are in the jail. You has too roll dices and you should either get same numbers on your dices or wait three turns in jail " << endl; 
                outfile << "Postion: " << field->Position << endl;
            }
            else if(field->Type == "Go"){
                outfile << "You made a circle, get your $200" << endl; 
            }
            
        }
        else if (field->Type == "Street") {
            outfile << "You reached a street " << field->Name << endl; 
            outfile << "Color: " << field->Color << endl;
            outfile << "Postion: " << field->Position << endl;
            outfile << "Price: $" << field->Price << endl;
            outfile << "Price to Build: $" << field->PriceBuild << endl;
            outfile << "Rent: $" << field->Rent << endl;
            outfile << "Rent with 1 House: $" << field->RentBuild1 << endl;
            outfile << "Rent with 2 Houses: $" << field->RentBuild2 << endl;
            outfile << "Rent with 3 Houses: $" << field->RentBuild3 << endl;
            outfile << "Rent with 4 Houses: $" << field->RentBuild4 << endl;
            outfile << "Rent with Hotel: $" << field->RentBuild5 << endl;
            outfile << "----------------------------------------" << endl;
        }
    }
    void displayFields(ostream& outfile = cout ) const{
        FieldData* current = headptr;
        do{ 
            displayField(outfile, current);
            current = current->nextField;
        }while(current != headptr);
    }
};

class Cards{ 
private: 
friend class Player; 
friend class Game; 
    struct Card{ 
        int ID; 
        string Tag; 
        string Type;
        string Category;
        string Name; 
        string Description;
        int Effect;
        Card(int id, string tag, string type, string category, string name, string description, int effect){
            ID = id; 
            Tag = tag; 
            Type = type; 
            Category = category; 
            Name = name;
            Description = description;
            Effect = effect;
        }
        bool operator==(const Card& other) const {
            return ID == other.ID; 
        } 
    };  
    vector<Card> chanceDeck;
    vector<Card> chestDeck; 
    vector<Card> chanceDeck2;
    vector<Card> chestDeck2; 
public: 

    

    Card getCardById(int id) {
        for (const Card& card : chanceDeck) {
            if (card.ID == id) {
                return card;
            }
        } 
    }

    int getId (Card &card) const{ 
        return card.ID; 
    }
    string getTag (Card &card) const{ 
        return card.Tag; 
    }   
    string getType (Card &card) const{ 
        return card.Type; 
    }   
    string getCategory (Card &card) const{ 
        return card.Category; 
    }  
    string getName (Card &card) const{ 
        return card.Name; 
    }
    string getDiscription (Card &card) const{ 
        return card.Description; 
    }
    int getEffect (Card &card) const{ 
        return card.Effect; 
    }    
    const vector<Card>& getChanceDeck() const {
        return chanceDeck;
    }
    const vector<Card>& getChestDeck() const {
        return chestDeck;
    }

    void addCard(int ID, string Tag, string Type, string Category, string Name, string Description, int Effect) {
        if(Type == "Chance"){
            chanceDeck.push_back(Card(ID, Tag, Type, Category, Name, Description, Effect));
        }
        else{
            chestDeck.push_back(Card(ID, Tag, Type, Category, Name, Description, Effect));
        }
    }

    void deleteCard(int index, vector<Card> &deck){
        if (index >= 0 && index < deck.size()) {
            deck.erase(deck.begin() + index);
        }
    }

    Card takeUserCard(vector<Card>& deck, vector<Card>& discardedDeck) { 
        if (isDeckEmpty(deck)) {
            deck = shuffleDeck(discardedDeck);
            discardedDeck.clear();
        }
        Card usedCard = deck.front();
        deck.erase(deck.begin());
        discardedDeck.push_back(usedCard);
        return usedCard;
    }
    
    bool isDeckEmpty(vector<Card>& deck){
        return deck.empty();
    } 

    vector<Card>& shuffleDeck(vector<Card>& deck) {
        auto rng = default_random_engine(chrono::system_clock::now().time_since_epoch().count());
        shuffle(begin(deck), end(deck), rng);
        return deck;
    }

    void displayCard(ostream& outfile, Card card){
        outfile << "Card ID: " << card.ID << "\n";
        outfile << "Tag: " << card.Tag << "\n";
        outfile << "Type: " << card.Type << "\n";
        outfile << "Category: " << card.Category << "\n";
        outfile << "Name: " << card.Name << "\n";
        outfile << "Description: " << card.Description << "\n";
        outfile << "Effect: " << card.Effect << "\n";
        outfile << "-----------------------\n";
    }

    void displayCards(ostream& outfile, const vector<Card>& deck) {
        for (const Card& card : deck) {
            displayCard(outfile, card);
        }
    }
    

};

class Player{
protected:
    string nameOfPlayer;
    int money;
    Board::FieldData* position; 
    vector<Cards::Card> cards; 
    bool inJail;
    vector<Board::FieldData*> properties; 
    vector<Board::FieldData*> loanProperties; 
    map<string, map<string, vector<Board::FieldData*> > > propertiesByTypeAndColor;

public:

    friend class Game; 
    friend class Board; 

    Player(Board& board, const string& playerName, int startingMoney) {
        inJail=false; 
        nameOfPlayer = playerName;
        money = startingMoney;
        position = board.getFirstPosition();
        propertiesByTypeAndColor[position->Type][position->Color].push_back(position);

    }
    ~Player(){  
        Board::FieldData* positionSaved = position; 
       
        for(Board::FieldData* property: properties){
            while (position->nextField != positionSaved) {
                if (property == position){
                    position->Owner =nullptr; 
                }
                position = position->nextField;
            }
        }
        for (Board::FieldData* loanproperty :loanProperties){
             while (position->nextField != positionSaved) {
                if (loanproperty == position){
                    position->Owner =nullptr; 
                }
                position = position->nextField;
            }
        }
    }
    int rollDice() {
    return (rand() % 6 + 1);
    }

    void displayPlayerCard () const{ 
        string answer;
        bool validChoice = false; 

        cout << "Money: "  << money << "$" << endl; 
        cout << "Position: " << position->Name << endl; 

        while (!validChoice) {
            cout << "Do you want to see your porperties (y/n)" << endl; 
            cin >> answer;
            if (answer == "y" || answer == "n") {
                validChoice = true;
            } 
            else {
                cout << "You entered an invalid character. Please enter 'y' or 'n'." << endl;
            }
        }
        if (answer == "y"){
                displayProperties();
            }
            else{
                return;
        }
    }

    void displayProperties() const {
        for (const auto& typePair : propertiesByTypeAndColor) {
            std::cout << "Type: " << typePair.first << std::endl;
            for (const auto& colorPair : typePair.second) {
                if (!colorPair.second.empty()) {
                    std::cout << "  Color: " << colorPair.first << std::endl;
                }
                for (const auto& property : colorPair.second) {
                    std::cout << "    - " << property->Name << " (Price: $" << property->Price << ")" << std::endl;
                }
            }
        }
    }
  

    void move(Board::FieldData* &position, int steps){
        while( steps >0 ){ 
            position = position->nextField;
            steps--; 
        }
    }
    void buyProperty(){
        if (position != nullptr and money >= position->Price){
            position->Owner= this; 
            properties.push_back(position);
        }  
        else { 
            cout << "You dont have enough money!" << endl; 
        }
    }

    bool ifPlayerHasAllColors(Board::FieldData* &property){
        int count = 0;
        for (Board::FieldData*  Property : properties){
            if( property == Property){
                count++; 
            }
        }
        if (property->Color == "Brown" or property->Color == "Blue" ){
            if (count == 2 ){ 
                return true; 
            }
            return false; 
        }
        else{ 
            if(count == 3){ 
                return true; 
            }
            return false; 
        }
        return false; 
    }
   
    void buildHouse(Board::FieldData* &property){ 
        if( ifPlayerHasAllColors(property) ){ 
            if (property->Owner == this){
                property->Number += 1; 
            }
        }
    }

    void payMoney(int& amount){ 
       
        money -= amount;
        
       
    }
    void receiveMoney(int& amount){
        money += amount;
    }

    void payRent(Player& owner) {
        if (position != nullptr && position->Owner == &owner) {
            int rentAmount = 0;
            switch (position->Number) {
                case 0:
                    rentAmount = position->Rent;
                    break;
                case 1:
                    rentAmount = position->RentBuild1;
                    break;
                case 2:
                    rentAmount = position->RentBuild2;
                    break;
                case 3: 
                    rentAmount = position->RentBuild3;
                    break; 
                case 4: 
                    rentAmount = position->RentBuild4;
                    break; 
                case 5:
                    rentAmount = position->RentBuild5; 
                    break;
                default:
                    rentAmount = position->Rent; 
                    break;
            }

            this->money -= rentAmount;
            owner.money += rentAmount;
        }
    }   
    void getCard (vector<Cards::Card>& deck, vector<Cards::Card>& discardedDeck, Cards::Card card, Cards cards) {
        cards.takeUserCard(deck, discardedDeck); 
        this->cards.push_back(card); 
    } 

    void useCard(Cards::Card& card, vector<Cards::Card>& mycards){
        auto it = find(mycards.begin(), mycards.end(), card); 
        if(it != mycards.end()){
            mycards.erase(it); 
        }
    }
    

    bool declareBankruptcy(){ 
        if (this->money <= 0){
            return true;
        }
        else return false; 
    }

   

};




class Game{ 
protected:

public: 
    Board board; 
    Cards cards;

    Game(){ 
    }

   

    vector <Player> startOfGame(Board& board) const{
        vector <Player> players; 
        int n = 0; 
        int budget; 
        string name; 
        cout<< "Choose number of players " << endl ; 
        cin >> n; 
        cout << "What is the statring budget? " << endl; 
        cin >> budget; 
        for (int i = 0; i<n; i++){
            cout << "What's the name of the " << i+1 << " player " << endl; 
            cin >> name; 
            Player player(board, name, budget); 
            players.push_back(player);
           
        }
        auto rng = default_random_engine(chrono::system_clock::now().time_since_epoch().count());
        shuffle(begin(players), end(players), rng);
        cout << "Let's start a game" << endl ; 
        return players; 
    }
    void mainGame(Board& board, Cards& card, vector<Player>& players){ 
        for (int i = 0; i < players.size(); i++ ){ 
            bool diceRolled = false;
            bool ready = false; 
            int action = 0;

            while (!ready){ 
                if(players[i].declareBankruptcy()){
                    loose(i, players); 
                }
                else { 
                    cout << players[i].nameOfPlayer << " , your turn" << endl; 
                    cout << "Options to do(give just a number of an action): " << endl << "1) View my Card." << endl << "2) Roll dice" << endl; 
                    cout << "9) Pass to the next person" << endl<< endl; 
                    cin >> action; 
                    switch (action)
                    {
                    case 1:
                        players[i].displayPlayerCard(); 
                        break;
                    case 2: 
                        while (!diceRolled){
                            int a = 0; 
                            int b = 0; 
                            a = players[i].rollDice();
                            b = players[i].rollDice();  

                            cout << "Dice №1 is " << a << ". Dice №2 is " << b << endl; 

                            if (a == b){ 
                                cout << "You got same number on dices. That means you have to roll them again" <<endl; 
                            }
                            else { 
                                diceRolled = true; 
                            }
                            players[i].move(players[i].position, a+b);
                            // cout << players[i].position->Name << " " << players[i].position->Type<< endl ; 

                            board.displayFieldGame(cout, players[i].position);
                            if(players[i].position->Owner == nullptr){ 
                                cout<< "Do u want to buy? (y/n)" << endl; 
                                bool validChoice = false; 
                                string answer = "";
                                cin >> answer; 
                                while (!validChoice) {
                                    if (answer == "y" || answer == "n") {
                                        validChoice = true;
                                    } 
                                    else {
                                        cout << "You entered an invalid character. Please enter 'y' or 'n'." << endl;
                                    }
                                }
                                if (answer == "y"){
                                        players[i].buyProperty();
                                    }
                                else{
                                    return;
                                }
                                
                            }
                        }
                        break; 
                    case 9: 
                        ready =true; 
                        break;
                    }
                }
            }
        }
    }
    void loose(int i, vector<Player>& players) {
        cout << "You don't have enough money to play. " << endl; 
            if (players[i].properties.size() == 0){ 
                cout << "You dont have any properties to get money. You lost" << endl; 
                /// players[i]; 
            }
            else{ 
                int sumMon = 0;
                for(Board::FieldData* property : players[i].properties){
                    sumMon += property->Price; 
                }
                if (sumMon/2 + players[i].money >= 0){
                    cout << "You can sell some properties to get money" << endl; 
                }
                else {
                    cout << "You dont have enough property to get money. You lost" << endl;
                }
            }
    }
}; 

bool openInputFile(ifstream &infile,const string& filename);
bool openOutputFile(ofstream &file, const string& filename);
void readData(ifstream &inputFile, Board& board);
void readData(ifstream &inputFile, Cards& cards); 

int main(){

    srand(time(NULL));
    ifstream infile1;
    ofstream outfile1;
    ifstream infile2;
    ofstream outfile2;

    string inputFile1Name = "board.csv";
    string outputFile1Name = "board.txt";
    string inputFile2Name = "cards.csv";
    string outputFile2Name = "cards.txt";

    bool infile1IsOpen = false; 
    bool outfile1IsOpen = false; 
    bool infile2IsOpen = false; 
    bool outfile2IsOpen = false; 

    Game game; 
    vector <Player> players; 
    

    infile1IsOpen = openInputFile(infile1, inputFile1Name);
    outfile1IsOpen = openOutputFile( outfile1, outputFile1Name);
    infile2IsOpen = openInputFile(infile2, inputFile2Name);
    outfile2IsOpen = openOutputFile( outfile2, outputFile2Name);
    
    if (!infile1IsOpen) {
        cout << "Input file 1 failed to open successfully..." << endl;
        exit(-1);
    }
    if (!outfile1IsOpen) {
        cout << "Output file failed 1 to open successfully..." << endl;
        exit(-1);
    }

    if (!infile2IsOpen) {
        cout << "Input file 2 failed to open successfully..." << endl;
        exit(-1);
    }
    if (!outfile2IsOpen) {
        cout << "Output file failed 2 to open successfully..." << endl;
        exit(-1);
    }

    readData(infile2, game.cards);
    readData(infile1, game.board);
    game.cards.displayCards(outfile2, game.cards.getChanceDeck());
    game.cards.displayCards(outfile2, game.cards.getChestDeck());
    game.board.displayFields(outfile1);

    players = game.startOfGame(game.board); 
    game.mainGame(game.board, game.cards, players); 

}

bool openInputFile(ifstream &infile,const string& filename)
{
    infile.open(filename);

    if (infile.is_open())
    {
        return true;
    }
    else {
        return false;
    }

}

bool openOutputFile(ofstream &file, const string& filename)
{
        file.open(filename);

        if (file.is_open())
        {
            return true;
        }
        else{
            return false;
        }


}

void readData(ifstream &inputFile, Board& board){
    string line; 
    string Name, Type, Color; 
    int Position, Price, PriceBuild, Rent;
    int RentBuild1, RentBuild2, RentBuild3, RentBuild4, RentBuild5, Number;
    getline(inputFile, line);
    int id = 0; 
    while (getline(inputFile, line)) {
        stringstream ss(line);
        getline(ss, Name, '|');
        getline(ss, Type, '|');
        getline(ss, Color, '|');
        string temp;
    
        getline(ss, temp, '|');
        Position = stoi(temp);
        getline(ss, temp, '|');
        Price = stoi(temp);
        getline(ss, temp, '|');
        PriceBuild = stoi(temp);
        getline(ss, temp, '|');
        Rent = stoi(temp);
        getline(ss, temp, '|');
        RentBuild1 = stoi(temp);
        getline(ss, temp, '|');
        RentBuild2 = stoi(temp);
        getline(ss, temp, '|');
        RentBuild3 = stoi(temp);
        getline(ss, temp, '|');
        RentBuild4 = stoi(temp);
        getline(ss, temp, '|');
        RentBuild5 = stoi(temp);
        getline(ss, temp, '|');
        Number = stoi(temp);
        

        board.appendFiled(Name, Type, Color, Position, Price,
                      PriceBuild, Rent, RentBuild1, RentBuild2,
                      RentBuild3, RentBuild4, RentBuild5, Number); 
        }
}

void readData(ifstream &inputFile, Cards& cards){
    string line; 
    string tag, type, category, name, discription; 
    int id, effect; 
    getline(inputFile, line);
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string temp;
        getline(ss, temp, '|');
        id= stoi(temp); 
        getline(ss, tag, '|');
        getline(ss, type, '|');
        getline(ss, category, '|');
        getline(ss, name, '|');
        getline(ss, discription, '|');
        getline(ss, temp, '|');
        effect = stoi(temp);
        cards.addCard(id, tag, type, category, name, discription, effect); 
    }

}
