#include <iostream> 
#include <string>  // in order to use getline() function

using namespace std;

class Pizza{
    private:
    string name;
    string size; //small, medium, big
    string *ingredients;//dyamic array
    string crust_type; //thick, normal, thin
    int ingredients_amount;
    int pizza_amount;
    public:
    Pizza();  // Default constructor
    Pizza(string size, string crust_type, int pizza_type); // Normal constructor
    Pizza(Pizza *&);  //  Copy constructor
    ~Pizza(); // Destructor
    void print_ingredients() const;
    void remove_ingredients(int *, int);
    void set_pizza_amount(int n){pizza_amount = n;}
    void print_details() const ; //to use in print_order function of Order class.
    int get_pizza_amount() {return pizza_amount;}
    int get_ingredients_amount(){return ingredients_amount;}
    string get_pizza_size() {return size;}
};
class Order{
    private:
    string customer;  //customers' name
    int *drinks; // it is a dynamic array(size = 4), 0. index is amount of cola, 1.index is amount of soda, 2.index is amount of icetea, 3.index is amount of fruit juice that ordered
    Pizza **pizzas;  // a dynamic array of pizzasa that ordered
    public:
    Order *next;
    Order(string,Pizza **&, int *);// constructer if customer wants to ha0ve09* 
    Order(string,Pizza **&);
    ~Order();
    float getPrice() const ;
    void printOrder() const ;
    string get_customer(){return customer;}
};
class OrderList{
    private:
    int n; // number of orders
    Order *head; // holds the first element of the orders' dynamic array
    public:
    OrderList();
    ~OrderList();
    void addOrder(Order *&);
    void listOrders() const ;
    Order* findOrder(string) const ;
    void deliverOrders(string);
    bool isExist(string) const ;
    Order* get_head(){return head;}
};
OrderList *order_list = new OrderList();
Pizza::Pizza(){
    this->size = "medium";
    this->crust_type = "normal";
    ingredients_amount = 1;
    ingredients = new string[ingredients_amount];
    ingredients[0] = "mozarella";
}
Pizza::Pizza(string size, string crust_type, int pizza_type){
    if(size=="small" || size == "medium" || size == "big") this->size = size; 
    if(crust_type == "thin" || crust_type=="normal" || crust_type=="thick") this->crust_type = crust_type;
    ingredients_amount = 6;
    if(pizza_type == 1){
        ingredients = new string[ingredients_amount];
        ingredients[0] = "mozarella";
        ingredients[1] = "chicken";
        ingredients[2] = "mushroom";
        ingredients[3] = "corn";
        ingredients[4] = "onion";
        ingredients[5] = "tomato";
        name = "Chicken Pizza";
    }
    if(pizza_type == 2){
        ingredients = new string[ingredients_amount];
        ingredients[0] = "mozarella";
        ingredients[1] = "broccoli";
        ingredients[2] = "pepperoni";
        ingredients[3] = "olive";
        ingredients[4] = "corn";
        ingredients[5] = "onion";
        name = "Broccoli Pizza";
    }
    if(pizza_type == 3){
        ingredients = new string[ingredients_amount];
        ingredients[0] = "mozarella";
        ingredients[1] = "sausage";
        ingredients[2] = "tomato";
        ingredients[3] = "olive";
        ingredients[4] = "mushroom";
        ingredients[5] = "corn";
        name = "Sausage Pizza";
    }
}
Pizza::~Pizza(){
    delete [] ingredients;
}
Pizza::Pizza(Pizza *&p){
    crust_type = p->crust_type;
    size = p->size;
    ingredients_amount = p->ingredients_amount;
    ingredients = new string[ingredients_amount];
    ingredients[0] = p->ingredients[0];
    ingredients[1] = p->ingredients[1];
    ingredients[2] = p->ingredients[2];
    ingredients[3] = p->ingredients[3];
    ingredients[4] = p->ingredients[4];
    ingredients[5] = p->ingredients[5];
    name = p->name;
    pizza_amount = p->pizza_amount;
}
void Pizza::print_ingredients() const{
    for (int i = 0; i < ingredients_amount; i++){
        cout << i+1 << ". " <<ingredients[i]<<endl;
    }
}
void boubleSort(int *arr, int size){  // to use in remove_ingredients func. Becouse elements of array
    int i,j; // parameter of remove_ingredients function have to be sorted from smallest to largest.
    for (i = 0; i < size; i++){ // if it is not, function can not run correctly when array elements are like {6,1}
        for (j = 1; j < size - i; j++){
            if (arr[j-1] > arr[j]){
                int temp = arr[j];
                arr[j] = arr[j-1];
                arr[j-1] = temp;
            }
        }
    }
}  

void Pizza::remove_ingredients(int *array_remove, int array_size){
    string *temp = new string[ingredients_amount - array_size]; //  temp dynamic array is created
    int i = 0, j = 0, k = 0;
    if(array_size > 0) boubleSort(array_remove, array_size);
    for(; i< this->ingredients_amount - array_size; i++){ 
        while(j == array_remove[k] -1 && k < array_size) {
            j++;
            k++;
        }
        temp[i] = this->ingredients[j];     
        j++;
    }
    this->ingredients_amount -= array_size;
    delete [] this->ingredients;
    this->ingredients = new string[this->ingredients_amount];
    for(i = 0; i<this->ingredients_amount; i++) {
        this->ingredients[i] = temp[i];
    }
    delete [] temp; // temp dynamic array is deleted
}
void Pizza::print_details() const { // just for use in print_order function of Order class.
    cout << endl << name <<"("; // becouse datas are private in Pizz class, so it is easier to write it in Pizza
    for (int i = 0; i < ingredients_amount; i++) cout << ingredients[i] <<", "; // class. it is like get_pizza_amount
    cout << ")" << endl << "size: " << size << ", crust: " << crust_type << endl; // function. 
}

Order::Order(string customer_name, Pizza **&p, int *drinkIdArray){
    customer = customer_name;
    drinks = new int[4];
    pizzas = new Pizza*[p[0]->get_pizza_amount()];
    for (int i = 0; i < 4; i++)  drinks[i] = drinkIdArray[i] ;
    for (int i = 0; i < p[0]->get_pizza_amount(); i++) pizzas[i] = p[i];
}
Order::Order(string customer_name, Pizza **&p){
    customer = customer_name;
    pizzas = new Pizza*[p[0]->get_pizza_amount()];
    for (int i = 0; i < p[0]->get_pizza_amount(); i++) pizzas[i] = p[i];
    drinks = new int[4];
    drinks[0] = drinks[1] = drinks[2] = drinks[3] = 0;
}
Order::~Order(){
    delete [] drinks;
    for (int i = 0; i < pizzas[0]->get_pizza_amount(); i++){//in this 4 line dynamic array of pizzas deleted
        delete pizzas[i]; // this pizzas array was an element of Order class
    } //  it was a dynamic array, so it should be deleted to prevent memory leek
    delete [] pizzas;
}
void Order::printOrder() const {
    cout << "- - - - - - - - - - - -" << endl;
    cout << "Name: " << customer << endl ;
    for (int i = 0; i < pizzas[0]->get_pizza_amount(); i++) pizzas[i]->print_details();
    cout << endl;
    if(drinks[0] != 0) cout << drinks[0] << " cola, ";
    if(drinks[1] != 0) cout << drinks[1] << " soda, ";
    if(drinks[2] != 0) cout << drinks[2] << " ice tea, ";
    if(drinks[3] != 0) cout << drinks[3] << " fruit juice, ";
    cout << endl << "- - - - - - - - - - - - -" << endl ;
}
float Order::getPrice() const {
    float result = 0;
    // in this 3 lines total price of pizzas is calculating...
    if(pizzas[0]->get_pizza_size() == "small") result += 15 * pizzas[0]->get_pizza_amount();
    else if(pizzas[0]->get_pizza_size() == "medium") result += 20 * pizzas[0]->get_pizza_amount();
    else if(pizzas[0]->get_pizza_size() == "big") result += 25 * pizzas[0]->get_pizza_amount();
    // now total price of drinks is calculating...
    if(drinks[0] != 0) result += 4 * drinks[0];
    if(drinks[1] != 0) result += 2 * drinks[1];
    if(drinks[2] != 0) result += 3 * drinks[2];
    if(drinks[3] != 0) result += 3.5 * drinks[3];
    return result;
}
OrderList::OrderList(){ // Default constractor of OrderList class
    head = NULL;
    n = 0;
}
OrderList::~OrderList(){ // Destructor of OrderList class
    Order *iter;
    while(head){ // all orders deleted here (linked list of orders)
        iter = head;
        head = head->next;
        delete iter;
    }
}

void OrderList::addOrder(Order *&order) {
    if(head == NULL){
        n++;
        head = order;
        order->next = NULL;
        return;
    }
    else{
        n++;
        Order *iter = head;
        while(iter->next != NULL) iter = iter->next;
        iter->next = order;
        order->next = NULL;
        return;
    }
}
void OrderList::listOrders() const {
    Order *iter = head;
    int x = 1;
    while (iter != NULL && x <= n){
        cout << x << endl;
        iter->printOrder();
        iter = iter->next;
        x++;
    }
}
Order* OrderList::findOrder(string customer_name) const {
    Order *iter = head;
    while (iter != NULL && iter->get_customer() != customer_name) iter = iter->next;
    return iter;
}
void OrderList::deliverOrders(string customer_name){
    Order *iter = head;
    if(head->get_customer() == customer_name){
        head = head->next;// head has to be changed when we deliver the order that at head.
        n--; // one of orders is delivered
        return;
    }
    else{
        Order *tail;
        while(iter->get_customer() != customer_name && iter->next != NULL) {
            tail = iter;
            iter = iter->next;
        }
        tail->next = iter->next;
        n--;
        return;
    }
}
bool OrderList::isExist(string customer_name) const {
    Order *iter = head;
    if(head->get_customer() == customer_name) return true;
    while(iter->get_customer() != customer_name && iter->next != NULL){
        iter = iter->next;
        if(iter->get_customer() == customer_name) return true;
    }
    return false;
}
void start(){ // a recursive function
    int operation;
    cout<<"Welcome to Unicorn Pizza!"<<endl
    <<"1. Add an order"<<endl<<"2. List orders"<<endl
    <<"3. Deliver order"<<endl<<"4. Exit"<<endl<<"Choose what to do: ";
    cin>>operation;
    while(operation != 1 && operation != 2 && operation != 3 && operation != 4){
        cout << "Please enter a valid input! (1/2/3/4)" << endl;
        cin >> operation;
    }
    if(operation ==1){ // ADD AN ORDER
    int  pizza_type, pizza_amount, i;
    string pizza_size, pizza_crust, customer_name;

    cout << "Pizza Menu" <<endl
    <<"1. Chicken Pizza (mozarella, chicken, mushroom, corn, onion, tomato)"<<endl
    <<"2. Broccoli Pizza (mozarella, broccoli, pepperoni, olive, corn, onion)"<<endl
    <<"3. Sausage Pizza (mozarella, sausage, tomato, olive, mushroom, corn)"<<endl
    << "0. Back to main menu"<<endl;
    cin >> pizza_type;
    while(pizza_type != 0 && pizza_type != 1 && pizza_type != 2 && pizza_type != 3){
        cout << "Please enter a valid input! (0/1/2/3)" << endl;
        cin >>pizza_type;
    }
    if(pizza_type == 0){
        start();
        return;
    }
    cout << "Select size: small (15 TL), medium (20 TL), big (25 TL)"<<endl;
    cin >> pizza_size;
    while(pizza_size != "small" && pizza_size != "medium" && pizza_size != "big"){ // for error message
        cout << "Please enter a valid input! (small/medium/big)" << endl;
        cin >>pizza_size;
    }
    cout << "Select crust type: thin, normal, thick" << endl;
    cin >> pizza_crust;
    while(pizza_crust != "thin" && pizza_crust != "normal" && pizza_crust != "thick"){//for error message
        cout << "Please enter a valid input! (thin/normal/thick)" << endl;
        cin >>pizza_crust;
    }
    cout << "Enter the amount:";
    cin >> pizza_amount;
    while(pizza_amount <= 0){
        cout << "Please enter a valid input!" << endl;
        cin >>pizza_amount;
    }
    Pizza **pizzas  = new Pizza*[pizza_amount];
    pizzas[0] = new Pizza(pizza_size, pizza_crust, pizza_type); // normal constructor is called here
    pizzas[0]->set_pizza_amount(pizza_amount);
    for (i = 1; i < pizza_amount; i++){
        pizzas[i] = new Pizza(pizzas[0]);
    }

    if(pizza_amount > 1){
        for(int j = 1; j < pizza_amount; j++){
            cout <<endl <<  "Please enter the number of the ingredient you want to remove from the pizza" <<endl;
            pizzas[0]->print_ingredients(); // it wont change, so it is better to use pizzas[0]
            cout << "Press 0 to save it." << endl;
            int  remove, *removeArr = new int[6]; // the array of ingredients that will be removed
            for (i = 0; i < 5; i++){ // it will ask up to 5 times, or there might be no ingredients in pizza, if the user enters 6 ingredients.
                cin >> remove;
                while(remove < 0 || remove > 6){ // for error message
                    cout << "Please enter a valid input! (1/2/3/4/5/6)" << endl;
                    cin >> remove;
                }
                if (remove == 0) break; //for "Press 0 to save it"
                removeArr[i] = remove;
            }
            pizzas[j]->remove_ingredients(removeArr, i);
            delete [] removeArr;
        }
    }
    cout<<"Please choose a drink."<<endl<<"0. no drink"<<endl<<"1. cola 4TL"
    <<endl<<"2 soda 2TL"<<endl<<"3. ice tea 3TL"<<endl<<"4. fruit juice 3.5 TL"
    <<endl<<"Press -1 for save your order."<<endl;
    int drink_id, *drinkArr = new int[4]; // amount of drinks that ordered.
    drinkArr[0]= drinkArr[1]= drinkArr[2]= drinkArr[3]=0;
    for(i = 0; true ; i++){
        cin >> drink_id;
        while (drink_id < -1 || drink_id > 4){ // for error message
            cout << "Please enter a valid input! (-1/0/1/2/3/4)" << endl;
            cin >> drink_id;
        }    
        if (drink_id == -1  || drink_id == 0) break;
        else if(drink_id == 1) drinkArr[0]++; 
        else if(drink_id == 2) drinkArr[1]++;
        else if(drink_id == 3) drinkArr[2]++;
        else if(drink_id == 4) drinkArr[3]++;
    }
    cout<<"Please enter your name:"<<endl;
    cin >> customer_name;
    Order *new_order;
    if(i == 0)  new_order = new Order(customer_name, pizzas);
    else new_order = new Order(customer_name, pizzas, drinkArr);
        
    delete [] drinkArr; // this array was a template array.it is deleting now.

    cout << endl << "Your order is saved, it will be delivered when it is ready..." << endl;
    new_order->printOrder();
    order_list->addOrder(new_order);
        
    start();
    return;
    }
    else if(operation == 2){ // LIST ORDER
        if(order_list->get_head() == NULL){cout << "Order list is empty." << endl;}
        else {order_list->listOrders();}
        start();
        return;
    }
    else if(operation == 3){// DELIVER ORDER
        if(order_list->get_head() == NULL){
            cout << "Order list is empty." << endl;
            start();
            return;
        }
        string customerName;
        order_list->listOrders();
        cout << "Please write the customer name in order to deliver his/herorder: ";
        cin >> customerName;
        if(!(order_list->isExist(customerName))){
            cout << "Wrong name!" << endl;
            start();
            return;
        }
        cout << "Following order is delivering..." << endl;
        Order *order = order_list->findOrder(customerName);
        order->printOrder();
        cout << "Total price: " << order->getPrice() << endl;
        while(true){
            char answer;
            string code;
            cout << "Do you have a promotion code? (y/n)" << endl;
            cin >> answer;
            while(answer != 'y' && answer != 'n'){ // for error message
                cout << "Please enter a valid input! (y/n) " << endl; // The user has to enter y or n.
                cin >> answer;
            }
            if(answer == 'n') break;
            else{
                cout << "Please enter your code: ";
                getline(cin, code); // It takes the empty character as input 
                getline(cin, code); // It takes the string as input
                if(code == "I am a student"){
                    cout << "Discounted price: " << order->getPrice() - order->getPrice() / 10 << endl;
                    break;
                }
                else   cout << "Promotion code is not accepted." << endl;
            }
        }
        order_list->deliverOrders(customerName);
        cout << "The order is delivered successfully!" << endl << endl;
        start();
        return;
    }
    else if(operation == 4){ // EXIT
        delete order_list;
        cout << "Goodbye..." << endl;
        return;
    }
}
int main(){
    start();
    return 0;
}