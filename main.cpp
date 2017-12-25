/**
 * @author Oliver Boamah
 * GROCERY MANAGEMENT SYSTEM
 * add, edit, delete categories, items
 * search categories, items
 * sell items
 *
 */
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;

// function prototypes
void category();
void item();
void sell();
void printMenu(string what);
bool saveToFile(char* file, vector<string> x);
vector<string> loadDataFromFile(char* file);
bool isExists(string str, vector<string> x);
bool add(string name, vector<string> strList, char* fileName);
bool edit(string name, vector<string> strList, char* fileName);
int getIdIndex(string key, vector<string> x);
bool remove(string name, vector<string> strList, char* fileName);
void viewAll(string name, vector<string> strList);
void searchFirstN(string name, vector<string> strList);
bool editItem(vector<string> strList, int index, string name, char* fileName);
void viewAllItems(vector<string> itemCatList, vector<string> itemNameList, vector<string> itemQuanList, vector<string> itemPriceList);
void searchItems(vector<string> itemCatList, vector<string> itemNameList, vector<string> itemQuanList, vector<string> itemPriceList);

int main()
{
    int choice;
    cout << "--------------------------------------------------------------" << endl << endl;
    cout << "\t\t GROCERY SHOP+ " << endl<< endl;
    cout << "--------------------------------------------------------------" << endl;

    cout << "\t 1- CATEGORIES " << endl;
    cout <<"\t 2- ITEMS " << endl;
    cout <<"\t 3- SELL " << endl;
    cin >> choice;
    cin.ignore();

    switch(choice)
    {
        case 1: category();
            break;
        case 2: item();
            break;
        case 3: sell();
            break;
    }

    return 0;
}


/** This function handles category operations **/
void category()
{
    // load list of categories from file
    vector<string> categoryList = loadDataFromFile("category/category.txt");

    system("cls");
    printMenu("CATEGORY");

    // accept choice from user
    int choice, a;
    cin >> choice;
    cin.ignore();

    switch(choice)
    {
        case 1:
               {
                    addLabel:
                    if(!add("Category name", categoryList, "category/category.txt")){
                        goto addLabel;
                    }else{
                        cout << "Category" << " added successfully! " << endl;
                        cout << "1- Category Menu " << endl;
                        cout << "Any Key- Exit " << endl;
                        cin >> a;
                        if(a == 1)
                        {
                            category();
                        }
                    }
               }
            break;
        case 2:
                {
                    editLabel:
                    if(!edit("Category name", categoryList, "category/category.txt")){
                        goto editLabel;
                    }else{
                        cout << "1- Category Menu " << endl;
                        cout << "Any Key- Exit " << endl;
                        cin >> a;
                        if(a == 1){
                            category();
                        }
                    }
                }
            break;
        case 3:
                {
                    removeLabel:
                    if(!remove("Category name", categoryList, "category/category.txt")){
                        goto removeLabel;
                    }else{
                        cout << "1- Category Menu " << endl;
                        cout << "Any Key- Exit " << endl;
                        cin >> a;
                        if(a == 1){
                            category();
                        }
                    }
                }
            break;
        case 4:
                {
                    viewAll("Category", categoryList);
                }
            break;
    }
}

/** This function handles item operations **/
void item()
{
    // load list of items from file
    vector<string> categoryList = loadDataFromFile("category/category.txt");
    vector<string> itemCategoryList = loadDataFromFile("item/category.txt");
    vector<string> itemNameList = loadDataFromFile("item/name.txt");
    vector<string> itemQuantityList = loadDataFromFile("item/quantity.txt");
    vector<string> itemPriceList = loadDataFromFile("item/price.txt");

    system("cls");
    printMenu("ITEM");

    // accept choice from user
    int choice, a;
    cin >> choice;
    cin.ignore();

    string category;

    switch(choice)
    {
        case 1:
               {
                    addLabel:
                    cout << "Enter Item category " << endl;
                    getline(cin, category);

                    // checks if category exists
                    int index = getIdIndex(category, categoryList) ;
                    if(index > -1) {

                       itemCategoryList.push_back(category);

                       if( !( (saveToFile("item/category.txt", itemCategoryList)) && add("Item name ", itemNameList, "item/name.txt")
                          && add("Item quantity", itemQuantityList, "item/quantity.txt") && add("Item price", itemPriceList, "item/price.txt"))) {
                            goto addLabel;
                        }
                        else{
                            cout << "Item added successfully! " << endl;
                            cout << "1- Item Menu " << endl;
                            cout << "Any Key- Exit " << endl;
                            cin >> a;
                            if(a == 1){
                                item();
                            }
                        }
                    }
                    else{
                       cout << "Category does not exist! " << endl;
                       goto addLabel;
                    }
               }
            break;
        case 2:
                {
                    editLabel:
                    string name;
                    cout << "Enter Item name " << endl;
                    getline(cin, name);

                    // checks if category exists
                    int index = getIdIndex(name, itemNameList) ;
                    if(index > -1) {
                        cout << "Enter new Item Category " << endl;
                        getline(cin, name);

                        if(getIdIndex(name, categoryList)> -1){

                            itemCategoryList[index] = name;

                            if(!( saveToFile("item/category.txt", itemCategoryList)
                             && editItem(itemNameList, index, "name", "item/name.txt")
                             && editItem(itemQuantityList, index, "quantity", "item/quantity.txt")
                             && editItem(itemPriceList, index, "price", "item/price.txt"))){
                                goto editLabel;
                            }else {
                                cout << "Item edited successfully! " << endl;
                                cout << "1- Category Menu " << endl;
                                cout << "Any Key- Exit " << endl;
                                cin >> a;
                                if(a == 1){
                                    item();
                                }
                            }
                        }
                        else{
                            cout << "Category " << name << " does not exist!" << endl;
                        }
                    }
                    else{
                       cout << "Item " << name << " does not exist! " << endl;
                       goto editLabel;
                    }


                }
            break;
        case 3:
                {
                    removeLabel:
                    string name;
                    cout << "Name of Item ? " << endl;
                    getline(cin, name);

                    int index = getIdIndex(name, itemNameList);
                    if(index > -1){

                         // remove str
                        itemCategoryList.erase(itemCategoryList.begin() + index);
                        itemNameList.erase(itemNameList.begin() + index);
                        itemQuantityList.erase(itemQuantityList.begin() + index);
                        itemPriceList.erase(itemPriceList.begin() + index);

                        if(!(saveToFile("item/category.txt", itemCategoryList)
                             && saveToFile("item/name.txt", itemNameList)
                             && saveToFile("item/quantity.txt", itemQuantityList)
                             && saveToFile("item/price.txt", itemPriceList) ) ){
                                goto removeLabel;
                        }else {
                            cout << "Item removed successfully! " << endl;
                            cout << "1- Category Menu " << endl;
                            cout << "Any Key- Exit " << endl;
                            cin >> a;
                            if(a == 1){
                                item();
                            }
                        }
                    } else {
                        cout << "Item does not exist! " << endl;
                        goto removeLabel;
                    }

                }
            break;
        case 4:
                {
                    viewAllItems(itemCategoryList, itemNameList, itemQuantityList, itemPriceList);
                }
            break;
        case 5:
                {
                    searchItems(itemCategoryList, itemNameList, itemQuantityList, itemPriceList);
                }
            break;
    }
}

/** This function handles account operations **/
void sell()
{
    // load list of items from file
    system("cls");
    vector<string> categoryList = loadDataFromFile("category/category.txt");
    vector<string> itemCategoryList = loadDataFromFile("item/category.txt");
    vector<string> itemNameList = loadDataFromFile("item/name.txt");
    vector<string> itemQuantityList = loadDataFromFile("item/quantity.txt");
    vector<string> itemPriceList = loadDataFromFile("item/price.txt");

    // displays all items
    viewAllItems(itemCategoryList, itemNameList, itemQuantityList, itemPriceList);

    vector <string> soldNameList;
    vector <int> soldQuanList;
    vector <double> soldPriceList;
    string soldName;
    int soldQuan = 0;
    double soldPrice, sumPrice;
    int sumQuan = 0;
    int n, a, index = -1;

    itemsNum:
    cout << "How many items do you want to sell " << endl;
    cin >> n;
    cin.ignore();

    if(n <= 0){
        cout << "Number of items cannot be less than or equals zero! " << endl;
        goto itemsNum;
    }
    for(int i = 0; i < n; i++)
    {
        nameLabel:
        cout << "Item name ? " << endl;
        getline(cin, soldName);

        index = getIdIndex(soldName, itemNameList);
        if(index > -1){
            quantityLabel:
            cout << "Item Quantity ? " << endl;
            cin >> soldQuan;
            cin.ignore();

            if(soldQuan < 0){
                cout << "Enter a positive number for quantity " << endl;
                goto quantityLabel;
            }else if(atoi(itemQuantityList[index].c_str()) == 0){
                cout << soldName << " is out of stock! " << endl;
                goto nameLabel;
            }

            if(soldQuan <= atoi(itemQuantityList[index].c_str()) ){

                 soldNameList.push_back(soldName);
                 soldQuanList.push_back(soldQuan);

                 soldPrice = soldQuan * atof(itemPriceList[index].c_str());
                 soldPriceList.push_back(soldPrice);
                 // sum up quantity and price;
                 sumQuan += soldQuan;
                 sumPrice += soldPrice;

                 // update quantity now
                 a = atoi(itemQuantityList[index].c_str()) - soldQuan;
                 std::stringstream s;
                 s << a;
                 itemQuantityList[index] = s.str();

                 // save updated quantity now
                 if (saveToFile("item/quantity.txt", itemQuantityList)){
                    cout << soldName << " added to Cart! " << endl;
                 }
            }else{
                cout << "Quantity greater than what is in stock! " << endl;
                cout << "Current quantity in Stock = " << itemQuantityList[index] << endl;
                goto quantityLabel;
            }
        }else {
            cout << "Item not found! " << endl;
            goto nameLabel;
        }
    }


    // view report
    system("cls");
    cout << "----------------------------------------------------------------------------------------" << endl;
    cout << "\t\t\t GROCERY SHOP+ INVOICE " << endl;
    cout << "\t\t ITEM NAME \t ITEM QUANTITY \t ITEM PRICE " << endl;

    for(int i = 0; i < n; i++ )
    {
        cout << "\t\t " << soldNameList[i] << " \t        " << soldQuanList[i] << " \t        " << soldPriceList[i] << endl;
    }
    cout << endl << "\t\t Total Quantity: " << sumQuan << endl;
    cout << "\t\t Total Price: " << sumPrice << endl;

    cout << "\t\t\t\t\t\t we care, we serve " << endl;
    cout << "------------------------------------------------------------------------------------------" << endl;

    int choice;
    cout << " 1- SELL AGAIN " << endl;
    cout << " Any Key - EXIT " << endl << endl;
    cin >> choice;
    if(choice == 1){
        sell();
    }


}

/** This function prints the menu **/
void printMenu(string what)
{
    string a = "\t\t 1- ADD ", b = "\t\t 2- EDIT ", c = "\t\t 3- REMOVE ", d = "\t\t 4- VIEW ALL ";
    cout << "--------------------------------------------------------------" << endl;
    cout << a + what << endl;
    cout << b + what << endl;
    cout << c + what << endl;
    cout << d + what << endl;
    cout << "--------------------------------------------------------------" << endl << endl;

}

/** This function saves a list of strings to file **/
bool saveToFile(char* file, vector<string> x)
{
  ofstream myfile (file);

  if (myfile.is_open()){
    for(int i = 0; i < x.size(); i++){
        myfile << x[i] << "\n" ;
    }
    myfile.close();
    return true;
  }

 return false;
}

/** This function returns a list of string read from the file specified **/
vector<string> loadDataFromFile(char* file)
{
    vector<string> fileLines;
    string line;
    ifstream inFile(file);

    if ( inFile.is_open() ) {
        while ( !inFile.eof() ) {
            getline(inFile, line);
            if(line != ""){
                fileLines.push_back(line);
            }
        }
        inFile.close();
    } else {
        // cerr << "Error opening file" << endl;
    }

    return fileLines;
}

/** This function return true if specified string exists in specified vector list **/
bool isExists(string str, vector<string> x)
{
    // convert all strings to lower case for correct comparisons
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);

    for(int i = 0; i < x.capacity(); i++){
         std::transform(x[i].begin(), x[i].end(), x[i].begin(), ::toupper);

         if(str == x[i]){
             return true;
         }
    }

    return false;
}

/** This function adds a string to the specified list and saves the list to the specified file if string does not already exist **/
bool add(string name, vector<string> strList, char* fileName)
{
    string input;
    string a = "Enter ";
    cout << a + name << endl;
    getline(cin, input);

    bool isExist = isExists(input, strList);

    if(name == "Item quantity"|| name == "Item price"){
        isExist = false;
    }

    if(!isExist){

        strList.push_back(input);
        if(saveToFile(fileName, strList)){

           return true;
        }
    }
    else{
        cout << name <<" " << input << " already exists " << endl;
    }

    return false;
}


/** This function returns the index of the specified string in the list **/
int getIdIndex(string key, vector<string> x)
{
    int index = -1;

    std::transform(key.begin(), key.end(), key.begin(), ::toupper);
    // find index of index_no entered
    for(int i = 0; i < x.size(); i++){

        // convert all strings to lower case for correct comparisons
        std::transform(x[i].begin(), x[i].end(), x[i].begin(), ::toupper);
        if(key == x[i]){
            index = i;
            break;
        }
    }

    return index;
}

/** This function adds a string to the specified list and saves the list to the specified file if string does not already exist **/
bool edit(string name, vector<string> strList, char* fileName)
{
    string input;
    string a = "Enter name of ", b = " you want to edit";
    cout << a + name + b << endl;
    getline(cin, input);

    int index = getIdIndex(input, strList);
    if(index > -1){

        a = "Enter new ";
        cout << a + name << endl;
        getline(cin, input);

        // override previous str
        strList[index] = input;

        if(saveToFile(fileName, strList)){
           cout << name << " edit successfully! " << endl;
           return true;
        }
    }
    else{
        cout << name << input << " does not exist! " << endl;
    }

    return false;
}

/** This function edits a string in a list **/
bool editItem(vector<string> strList, int index, string name, char* fileName)
{
    string input;
    cout << "Enter new Item " << name << endl;
    getline(cin, input);

    // override previous string
    strList[index] = input;

    if(saveToFile(fileName, strList)){
        return true;
    }

    return false;
}

/** This function removes the specified str from the specified list and saves to the specified file **/
bool remove(string name, vector<string> strList, char* fileName)
{
    string input;
    string a = "Enter name of ", b = " you want to remove";
    cout << a + name + b << endl;
    getline(cin, input);

    int index = getIdIndex(input, strList);

    if(index > -1){

        // remove str
        strList.erase(strList.begin() + index);

        if(saveToFile(fileName, strList)){
           cout << name << " removed successfully! " << endl;
           return true;
        }
    }
    else{
        cout << name << " " << input << " does not exist! " << endl;
    }

    return false;
}

/** This function displays all the categories in the category list **/
void viewAll(string name, vector<string> strList)
{
    int sum = 0;
    cout << name << endl;
    for(int i = 0; i < strList.size(); i++){

        if(strList[i] != "")
        {
            cout << strList[i] << endl;
            sum ++;
        }
    }
    cout << "Total Categories: " << sum << endl;

    int a;
    cout << endl << "1- Category Menu " << endl;
    cout << "Any key- Exit " << endl;
    cin >> a;

    if(a == 1){
        category();
    }

}

/** This function searches for a matching firstNCharacters match and displays the results **/
void searchFirstN(string name, vector<string> strList)
{
    string key;
    string a = "Enter ";
    cout << a << name << " full name or starting characters " << endl;
    getline(cin, key);

    system("cls");

    // SEARCH RESULTS AREA
    cout << "------------------------------------------------ " << endl;
    cout << "SEARCH RESULTS" << endl;
    cout << "------------------------------------------------ " << endl;

    // convert all strings to lower case for correct comparisons
    std::transform(key.begin(), key.end(), key.begin(), ::toupper);

    for(int i = 0; i < strList.size(); i++){

        std::transform(strList[i].begin(), strList[i].end(), strList[i].begin(), ::toupper);

        if(strList[i].rfind(key, 0) == 0) {
            cout << strList[i] << endl;
        }
    }

}

/** This function displays the list of all items **/
void viewAllItems(vector<string> itemCatList, vector<string> itemNameList, vector<string> itemQuanList, vector<string> itemPriceList)
{

    system("cls");
    cout << "--------------------------------------------------------------------------" << endl;
    cout << "\t\t\t  ALL ITEMS " << endl;
    cout << "\t\t CATEGORY \t   NAME \t QUANTITY \t PRICE" << endl;
    for(int i = 0; i < itemNameList.size(); i++)
    {
        if(itemNameList[i] != "") {
             cout << "\t\t " << itemCatList[i] << " \t   " << itemNameList[i] << " \t  " << itemQuanList[i]<< " \t          " << itemPriceList[i] << endl;
        }
    }
    cout <<"---------------------------------------------------------------------------" << endl;

}

/** This function displays a list of all items matching a search pattern **/
void searchItems(vector<string> itemCatList, vector<string> itemNameList, vector<string> itemQuanList, vector<string> itemPriceList)
{
    string key;
    cout << "Enter item name or starting characters " << endl;
    getline(cin, key);

    system("cls");
    cout << "--------------------------------------------------------------------------" << endl;
    cout << "\t\t SEARCH RESULTS - ALL ITEMS " << endl;
    cout << "\t\t CATEGORY \t NAME \t QUANTITY \t PRICE" << endl;
    for(int i = 0; i < itemNameList.size(); i++)
    {
        if(itemNameList[i].rfind(key, 0) == 0) {
            cout << "\t\t" << itemCatList[i] << " \t " << itemNameList[i] << " \t " << itemQuanList[i]<< " \t " << itemPriceList[i] << endl;
        }
    }
    cout <<"---------------------------------------------------------------------------" << endl;

    int a;
    cout << "1- Category Menu " << endl;
    cout << "Any Key- Exit " << endl;
    cin >> a;
    if(a == 1) {
        item();
    }
}












