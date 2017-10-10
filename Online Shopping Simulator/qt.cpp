#include <QMessageBox>
#include <QString>
#include <QListWidget>
#include <QApplication>
#include <QTextEdit>
#include "qt.h"
#include "hash.h"
#include "mydatastore.h"
#include "user.h"
#include "product.h"
#include "msort.h"
#include "review.h"
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <cmath>
#include <limits>
#include <iomanip>


//added this
//login window first and need to pass to get to mainwindow 
LoginWindow::LoginWindow(MainWindow* mw, MyDataStore* ds){
	dl = ds;
	ml = mw;
	this->setWindowTitle("Login");
	loginWindowLayout= new QVBoxLayout();
	this->setLayout(loginWindowLayout);

	usernameInput = new QLineEdit();
	loginWindowLayout->addWidget(usernameInput);
	usernameInput->setPlaceholderText("Enter username");

	passwordInput = new QLineEdit();
	loginWindowLayout->addWidget(passwordInput);
	passwordInput->setPlaceholderText("Enter password");

	loginButton = new QPushButton("Login");
	loginWindowLayout->addWidget(loginButton);
	quitLoginButton = new QPushButton("Quit");
	loginWindowLayout->addWidget(quitLoginButton);
	QObject::connect(quitLoginButton, SIGNAL(clicked()), this, SLOT(quitLogin()));
	newUserButton = new QPushButton("New User");
	loginWindowLayout->addWidget(newUserButton);
	connect(loginButton, SIGNAL(clicked()), this, SLOT(goToMain()));
	connect(newUserButton, SIGNAL(clicked()), this, SLOT(newUserLogin()));
	addMainWindow_window = mw;
}
LoginWindow::~LoginWindow(){
}
//will quit the program 
void LoginWindow::quitLogin(){
	QApplication::exit();
}

//logs in for a new user if valid password < 8 characters 
void LoginWindow::newUserLogin(){	
	HashHelper h;
	QString usernameLogin = usernameInput->text();
	std::string username = usernameLogin.toStdString();
	QString passwordLogin = passwordInput->text();
	std::string password = passwordLogin.toStdString();
	std::vector<User*> u = dl->getUser();

	if(usernameInput->text().isEmpty() || passwordInput->text().isEmpty()){
		QMessageBox mymsg(this);  
		mymsg.setText("Add username or password");
		mymsg.exec();
		passwordInput->clear();
		usernameInput->clear();	
	}
	else{
		for(unsigned int j=0; j<u.size(); j++){
			if(username == u[j]->getName() || h.Hasher(password) == u[j]->getHash()){
				QMessageBox mymsg(this);  
				mymsg.setText("Username Already Exists");
				mymsg.exec();
				passwordInput->clear();
				usernameInput->clear();	
			}
		}
		if(password.length() > 8){
			QMessageBox mymsg(this);  
			mymsg.setText("Password is Longer Than 8 Characters");
			mymsg.exec();
			passwordInput->clear();
			usernameInput->clear();	
		}
		else{

			unsigned long long newUserHash = h.Hasher(password);
			User* user = new User(username, 100.00, 0, newUserHash);
			dl->addUser(user); 

			ml->usernameLayout = new QVBoxLayout;
			ml->userList = new QComboBox(addMainWindow_window);
			std::string uName = ml->db->chooseUser(username);
			QString n = QString::fromStdString(uName);
			ml->userList->addItem(n);
			ml->usernameLayout->addWidget(ml->userList);
			ml->buttonDisplayLayout->addLayout(ml->usernameLayout);

			addMainWindow_window->show();
			this->hide();
			return;	
		}			
	}
}

//user needs to login with a valid username and password 
//or else and error message will pop up
void LoginWindow::goToMain(){
	HashHelper h;
	QString usernameLogin = usernameInput->text();
	QString passwordLogin = passwordInput->text();
	std::stringstream uu(usernameLogin.toStdString());
	std::stringstream pp(passwordLogin.toStdString());
	std::string pWord;
	std::string uWord;

	std::vector<User*> u = dl->getUser();
	std::string user_name;
	while(pp >> pWord && uu >> uWord){ 
		for(unsigned int j=0; j<u.size(); j++){
			QString n = QString::fromStdString(u[j]->getName());
			std::string nInput = n.toStdString();
			if(uWord == nInput){
				user_name = u[j]->getName();

				if(h.Hasher(pWord) == u[j]->getHash()){

					ml->usernameLayout = new QVBoxLayout;
					ml->userList = new QComboBox(addMainWindow_window);
					std::string uName = ml->db->chooseUser(user_name);
					QString n = QString::fromStdString(uName);
					ml->userList->addItem(n);
					ml->usernameLayout->addWidget(ml->userList);
					ml->buttonDisplayLayout->addLayout(ml->usernameLayout);

					addMainWindow_window->show();
 					this->hide();
					return;					
				}
				//ERROR MESSAGE 
				else{
					passwordInput->clear();
					usernameInput->clear();		
					QMessageBox mymsg(this);  
					mymsg.setText("Username or Password is Wrong");
					mymsg.exec();
					
				}		
			}
		}
		//ERROR MESSAGE 
		std::map<std::string, User* > map_u = dl->getMapUser();
		if(map_u.find(uWord) == map_u.end()){
			passwordInput->clear();
			usernameInput->clear();		
			QMessageBox mymsg(this);  
			mymsg.setText("Username or Password is Wrong");
			mymsg.exec();
			
		}	
	}
}

//
//passes in a mydatastore object to be able to reference 
//mydatastore functions and data members 
//also defines all the widgets and connects them to slots 
//while also placing/organizing them 
MainWindow::MainWindow(MyDataStore* ds)
{

	//take in a data store 
	db = ds;
	this->setWindowTitle("Amazon");

	// Overall layout
	overallLayout = new QVBoxLayout();

	//for people to type in keywords and search for
	//matching products 
	productNameInput = new QLineEdit();
	overallLayout->addWidget(productNameInput);
	productNameInput->setPlaceholderText("Enter search words");
	searchButton = new QPushButton("Search");
	connect(searchButton, SIGNAL(clicked()), this, SLOT(addProduct()));
	overallLayout->addWidget(searchButton);	
	

	//ADDED THIS
	reccomendation_window = new QWidget;
	reccomendation_window->setWindowTitle("Product Recomendations");
	productReccButton = new QPushButton("Product Recomendations");
	connect(productReccButton, SIGNAL(clicked()), this, SLOT(reccomendation()));
	overallLayout->addWidget(productReccButton);

	recListWidget = new QListWidget();
	recWindowLayout = new QVBoxLayout();
	reccomendation_window->setLayout(recWindowLayout);
	recWindowLayout->addWidget(recListWidget);
	doneRecButton = new QPushButton("Done");
	connect(doneRecButton, SIGNAL(clicked()), this, SLOT(doneWithRec()));
	recWindowLayout->addWidget(doneRecButton);

	//uses radio buttons for AND OR selection
	buttonDisplayLayout = new QHBoxLayout;
	overallLayout->addLayout(buttonDisplayLayout);
	buttonAnd = new QRadioButton("AND", this);
	buttonOr = new QRadioButton("OR", this);
	createAndOr = new QButtonGroup();
	createAndOr->addButton(buttonAnd);
	createAndOr->addButton(buttonOr);
	buttonOr->setChecked(true);
	buttonAnd->setChecked(false);
	buttonDisplayLayout->addWidget(buttonAnd);
	buttonDisplayLayout->addWidget(buttonOr);


	//add review button
	addReviewButton = new QPushButton("Add Review");
	buttonDisplayLayout->addWidget(addReviewButton);
	connect(addReviewButton, SIGNAL(clicked()), this, SLOT(addReview()));
	productDisplayLayout = new QHBoxLayout();
	overallLayout->addLayout(productDisplayLayout);
	productNameDisplay = new QLabel("");
	productDisplayLayout->addWidget(productNameDisplay);
	productDisplayLayout->addStretch();
	//more buttons 
	andOrDisplayLayout = new QVBoxLayout();
	productDisplayLayout->addLayout(andOrDisplayLayout);
	buttonRating = new QPushButton("Sort by Rating");
	buttonAlpha = new QPushButton("Sort Alphabetically");
	connect(buttonRating, SIGNAL(clicked()), this, SLOT(sortRating()));
	connect(buttonAlpha, SIGNAL(clicked()), this, SLOT(sortAlpha()));	
	andOrDisplayLayout->addWidget(buttonAlpha);
	andOrDisplayLayout->addWidget(buttonRating);
	addCartButton = new QPushButton("Add to Cart");
	connect(addCartButton, SIGNAL(clicked()), this, SLOT(addCart()));
	andOrDisplayLayout->addWidget(addCartButton);
	viewCartButton = new QPushButton("View Cart");
	connect(viewCartButton, SIGNAL(clicked()), this, SLOT(addView()));
	andOrDisplayLayout->addWidget(viewCartButton);

	//input for a filename a user wants to save to 
	fileNameInput = new QLineEdit();
	andOrDisplayLayout->addWidget(fileNameInput);
	fileNameInput->setPlaceholderText("Enter a filename");
	buttonSave = new QPushButton("Save");
	connect(buttonSave, SIGNAL(clicked()), this, SLOT(save()));
	andOrDisplayLayout->addWidget(buttonSave);	
	buttonQuit = new QPushButton("Quit");
	QObject::connect(buttonQuit, SIGNAL(clicked()), qApp, SLOT(quit()));
	andOrDisplayLayout->addWidget(buttonQuit);	
	//will display all the products 
	productListWidget = new QListWidget();
	connect(productListWidget, SIGNAL(currentRowChanged(int)), this, SLOT(viewReviews(int)));
	productDisplayLayout->addWidget(productListWidget);
	//reviews widget will display all the reviews 
	reviewListWidget = new QListWidget();
	productDisplayLayout->addWidget(reviewListWidget);
	formLayout = new QVBoxLayout();
	overallLayout->addLayout(formLayout); 	
	//FOR VIEWING IN NEW WINDOW	
	new_window = new QWidget;
	new_window->setWindowTitle("Cart");
	viewDisplayLayout = new QHBoxLayout();
	viewDisplayLayoutButtons = new QVBoxLayout();
	new_window->setLayout(viewDisplayLayout);
	viewDisplayLayout->addLayout(viewDisplayLayoutButtons);
	closeButton = new QPushButton("Close");
	buyCartButton = new QPushButton("Buy");
	removeButton = new QPushButton("Remove");
	viewDisplayLayoutButtons->addWidget(buyCartButton);
	viewDisplayLayoutButtons->addWidget(closeButton);
	viewDisplayLayoutButtons->addWidget(removeButton);
	connect(removeButton, SIGNAL(clicked()), this, SLOT(remove()));
	connect(buyCartButton, SIGNAL(clicked()), this, SLOT(addBuy()));
	//displays all objects in cart 
	cartListWidget = new QListWidget();
	viewDisplayLayout->addWidget(cartListWidget);
	connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
	//new window to add reviews 
	addReview_window = new QWidget;
	addReview_window->setWindowTitle("Adding a Review");
	addReviewDisplayLayout = new QVBoxLayout();
	addReview_window->setLayout(addReviewDisplayLayout);
	addReviewButtonDisplayLayout = new QHBoxLayout;
	addReviewDisplayLayout->addLayout(addReviewButtonDisplayLayout);
	buttonOne = new QRadioButton("1", this);
	buttonTwo = new QRadioButton("2", this);
	buttonThree = new QRadioButton("3", this);
	buttonFour = new QRadioButton("4", this);
	buttonFive = new QRadioButton("5", this);
	createRating = new QButtonGroup();
	createRating->addButton(buttonOne);
	createRating->addButton(buttonTwo);
	createRating->addButton(buttonThree);
	createRating->addButton(buttonFour);
	createRating->addButton(buttonFive);
	buttonOne->setChecked(true);
	buttonTwo->setChecked(false);
	buttonThree->setChecked(false);
	buttonFour->setChecked(false);
	buttonFive->setChecked(false);
	addReviewButtonDisplayLayout->addWidget(buttonOne);
	addReviewButtonDisplayLayout->addWidget(buttonTwo);
	addReviewButtonDisplayLayout->addWidget(buttonThree);
	addReviewButtonDisplayLayout->addWidget(buttonFour);
	addReviewButtonDisplayLayout->addWidget(buttonFive);
	reviewInput = new QLineEdit;
	addReviewDisplayLayout->addWidget(reviewInput);	
	reviewInput->setPlaceholderText("Enter review text");
	year = new QComboBox(this); 
	for(int j=2016; j<=2030; j++){
		stringstream ss;
		ss<<j;
		std::string s;
		ss>>s;
		QString n = QString::fromStdString(s);
		year->addItem(n);
	}
	//if number is less than ten than add 
	//a leading 0 
	month = new QComboBox(this); 
	for(int i=1; i<=12; i++){ 
		stringstream jj;
		jj << 0;
		std::string n;
		jj >> n;
		if(i<10){
			stringstream ss;
			ss<<i;
			std::string s;
			ss>>s;
			std::string num = n+s;
			QString n = QString::fromStdString(num);
			month->addItem(n);		
		}
		else{
			stringstream ss;
			ss<<i;
			std::string s;
			ss>>s;
			QString n = QString::fromStdString(s);			
			month->addItem(n);
		}
	}
	day = new QComboBox(this); 
	for(int y=1; y<=31; y++){
		stringstream jj;
		jj << 0;
		std::string n;
		jj >> n;
		if(y<10){
			stringstream ss;
			ss<<y;
			std::string s;
			ss>>s;
			std::string num = n+s;
			QString n = QString::fromStdString(num);
			day->addItem(n);		
		}
		else{
			stringstream ss;
			ss<<y;
			std::string s;
			ss>>s;
			QString n = QString::fromStdString(s);			
			day->addItem(n);
		}
	}
	addReviewDateDisplayLayout = new QHBoxLayout;
	addReviewDisplayLayout->addLayout(addReviewDateDisplayLayout);
	addReviewDateDisplayLayout->addWidget(year);
	addReviewDateDisplayLayout->addWidget(month);
	addReviewDateDisplayLayout->addWidget(day);
	addItButton = new QPushButton("Add");
	closeReviewButton = new QPushButton("Close");
	addReviewDisplayLayout->addWidget(addItButton);
	addReviewDisplayLayout->addWidget(closeReviewButton);	
	connect(addItButton, SIGNAL(clicked()), this, SLOT(addIt()));	
	connect(closeReviewButton, SIGNAL(clicked()), this, SLOT(closeReview()));


	setLayout(overallLayout);
}
//destructor to delete QT objects 
MainWindow::~MainWindow(){
	delete viewCartButton;
	delete buyCartButton;
	delete addCartButton;
	delete removeButton;
	delete buttonRating;
	delete buttonAlpha;
	delete buttonSave;	
	delete closeButton;
	delete addReviewButton;
	delete closeReviewButton;
	delete addItButton;
	delete buttonQuit;
}

//uses datastore object to call search function
//if the AND radion button is clicked
//then will call search with a value of 0
//else (if OR is clicked) will call with a value of 1
//and will return a vector of Product* that matches the key words 
std::vector<Product*> MainWindow::addSearch(){ 
	QString input = productNameInput->text();
	std::stringstream ss(input.toStdString());
	std::string word;
	w.clear();
	while(ss >> word){ 
		word = convToLower(word);
		w.push_back(word); 
	}
	if(buttonAnd->isChecked()){
		searchResult = db->search(w, 0); 
	}
	if(buttonOr->isChecked()){
		searchResult = db->search(w,1);
	}
	return searchResult;
}
//will sort the products alphabetically 
void MainWindow::sortAlpha(){
	typename MainWindow::AlphaStrComp alphaComp;
	mergeSort (p, alphaComp);
	productListWidget->clear();
	for(unsigned int j=0; j<p.size(); j++){
		std::string name = p[j]->getName(); 
		double pr = p[j]->getPrice();
		std::ostringstream ss;
		ss << pr;
		std::string pri = ss.str();
		std::string full = name + "\n" + pri;
		QString n = QString::fromStdString(full);
    	productListWidget->addItem(n); 
		productNameInput->setText(""); 
	}
}
//will sort the products by ratings 
void MainWindow::sortRating(){
	typename MainWindow::LengthDoubleComp doubleComp;
	mergeSort (p, doubleComp);
	productListWidget->clear();
	for(unsigned int j=0; j<p.size(); j++){
		std::string name = p[j]->getName(); 
		double pr = p[j]->getPrice();
		std::ostringstream ss;
		ss << pr;
		std::string pri = ss.str();
		std::string full = name + "\n" + pri;
		QString n = QString::fromStdString(full);
    	productListWidget->addItem(n); 
		productNameInput->setText(""); 
	}
}
//will sort the reviews by their dates 
void MainWindow::sortDate(){
	typename MainWindow::DateComp dateComp;
	mergeSort (product_review, dateComp);
	reviewListWidget->clear();
	for(unsigned int i = 0; i < product_review.size(); i++){
		std::string name = product_review[i]->prodName;
		std::ostringstream ss;
		ss << product_review[i]->rating;
		std::string rates = ss.str();
		std::string user = product_review[i]->username;
		std::string date = product_review[i]->date;
		std::string text = product_review[i]->reviewText;
		std::string full = rates + " " + user + " " + date + " " + text;
		QString n = QString::fromStdString(full);
		reviewListWidget->addItem(n);  
	}
}
//will return the chosen user's name 
std::string MainWindow::chooseUser(){
	std::vector<User*> u = db->getUser();
	std::string user_name;
	for(unsigned int j=0; j<u.size(); j++){
		QString n = QString::fromStdString(u[j]->getName());
		if(userList->currentText() == n){
			user_name = u[j]->getName();
		}
	}
	return user_name;
}

//will open up a new window when the View button
//is clicked that shows the chosen user's cart 
void MainWindow::addView(){
	std::string user = chooseUser();
	cart_p = db->cart_products(user);
	cartListWidget->clear();
	for(unsigned int i = 0; i < cart_p.size(); i++){
		std::string name = cart_p[i]->getName(); 
		double pr = cart_p[i]->getPrice();
		std::ostringstream ss;
		ss << pr;
		std::string pri = ss.str();
		std::string full = name + "\n" + pri;
		QString n = QString::fromStdString(full);
		cartListWidget->addItem(n);  
	}
	new_window->show();
}
//will use the selected product's index passed in and the datastore 
//object to call the datastore function that gets the selected product's reviews 
//and will sort them 
void MainWindow::viewReviews(int productIndex){
	if(productIndex < 0){
		return;
	}
	product_review = db->gr(p[productIndex]->getName());
	sortDate();
}
//will close the new window when the Close Button is clicked 
void MainWindow::close(){
	new_window->hide();
}
//the Remove button is connected to this function
//which calls the removeProduct function that passes
//in the currently selected product in the cart's index 
void MainWindow::remove(){
	removeProduct(cartListWidget->currentRow());
}
//uses the passed in index to remove
//the selected product from the user's cart
//calls the datastore functions that remove items from 
//the cart and the one that returns the products
//for the selected user's cart 
//will update the cartListWidget every time something
//is removed  
void MainWindow::removeProduct(int productIndex){
	std::string user = chooseUser();
	vector<Product* >products = db->getProduct();
	db->removeCart(user, productIndex);
	cart_p = db->cart_products(user);
	cartListWidget->clear();
	for(unsigned int i = 0; i < cart_p.size(); i++){
		std::string name = cart_p[i]->getName(); 
		double pr = cart_p[i]->getPrice();
		std::ostringstream ss;
		ss << pr;
		std::string pri = ss.str();
		std::string full = name + "\n" + pri;
		QString n = QString::fromStdString(full);
		cartListWidget->addItem(n);  
	}	
}
//this calls the buyCart function from the datastore
//will go down the cart and only buy the items 
//the person has enough money for and update the cart
void MainWindow::addBuy(){ 
	std::string user = chooseUser();
	db->buyCart(user);
	removeProduct(cartListWidget->currentRow());
}
//the Add to Cart button connects to this function
//which calls the addToCart function that
//passes in the currently selected product's index
void MainWindow::addCart(){
	addToCart(productListWidget->currentRow());
}
//uses the datastore functions to add the 
//product with the selected index to the cart
//and the function that returns the selected user's cart
void MainWindow::addToCart(int productIndex){
	if(productListWidget->currentRow() < 0){
		return;
	}
	std::string user = chooseUser();
	vector<Product* >products = db->getProduct();
	for(unsigned int i = 0; i < products.size(); i++){
		if(products[i] == p[productIndex]){
			db->addCart(user,p[productIndex]);
			cart_p = db->cart_products(user);
		}
	}
	cartListWidget->clear();
	for(unsigned int i = 0; i < cart_p.size(); i++){
		std::string name = cart_p[i]->getName(); 
		double pr = cart_p[i]->getPrice();
		std::ostringstream ss;
		ss << pr;
		std::string pri = ss.str();
		std::string full = name + "\n" + pri;
		QString n = QString::fromStdString(full);
		cartListWidget->addItem(n);  
	}
}
//will call the addSearch function from above
//and will print the vector of products to the 
//productListWidget 
void MainWindow::addProduct(){
	if(productNameInput->text().isEmpty()){
		return;
	}
	p = addSearch();
    productListWidget->clear();
	for(unsigned int j=0; j<p.size(); j++){
		std::string name = p[j]->getName(); 
		double pr = p[j]->getPrice();
		std::ostringstream ss;
		ss << pr;
		std::string pri = ss.str();
		std::string full = name + "\n" + pri;
		QString n = QString::fromStdString(full);
    	productListWidget->addItem(n); 
		productNameInput->setText(""); 
	}
}
//will call the datastore object dump 
//and will print into whatever file name a person inputs 
void MainWindow::save(){ 
	if(fileNameInput->text().isEmpty()){
		return;
	}
	QString input = fileNameInput->text();
	std::string file = input.toStdString();
	ofstream ofile(file.c_str());
    db->dump(ofile);
    ofile.close();
}
//will call the inputReview function and will 
//add the retrieved Review to the selected product 
void MainWindow::addTheReviews(int productIndex){
	if(productIndex < 0){
			return;
	}
	vector<Product* > products = db-> getProduct();
	for(unsigned int i = 0; i < products.size(); i++){
		if(products[i] == p[productIndex]){
			Review* r = inputReview();
			db->addReview(r);
			product_review = db->gr(p[productIndex]->getName());
			sortDate();
		}
	}
}
//will only open up the window to add reviews if
//a product is chosen 
void MainWindow::addReview(){
	int index = productListWidget->currentRow();
	if(index >= 0){
		addReview_window->show();		
	}
}
//will close the add review window 
void MainWindow::closeReview(){
	reviewInput->setText(""); 
	addReview_window->hide();
}
//if the person clickes the Add button will 
//also close the add review window AND add the
//review to the selected product because it 
//calls the addTheReviews button
void MainWindow::addIt(){
	int productIndex = productListWidget->currentRow();
	addTheReviews(productIndex);
	reviewInput->setText(""); 
	addReview_window->hide();
}
//this all gets the components for the new 
//review such as the date, the user, the rating
//and the review text 
//use radiobuttons for the ratings, a lineedit 
//for the review text, and three comboboxes to
//get the three parts of the date (YYYY-MM-DD)
Review* MainWindow::inputReview(){
	int i;
	std::string s;
	if(buttonOne->isChecked()){ 
		i = 1;
		stringstream ss;
		ss<<i;
		ss>>s;
	}
	if(buttonTwo->isChecked()){
		i = 2;
		stringstream ss;
		ss<<i;
		ss>>s;
	}
	if(buttonThree->isChecked()){ 
		i = 3;
		stringstream ss;
		ss<<i;
		ss>>s;
	}
	if(buttonFour->isChecked()){
		i = 4;
		stringstream ss;
		ss<<i;
		ss>>s;
	}
	if(buttonFive->isChecked()){
		i = 5;
		stringstream ss;
		ss<<i;
		ss>>s;
	}

	QString input = reviewInput->text();
	std::stringstream jj(input.toStdString());
	std::string word;
	reviewText.clear();
	while(jj >> word){ 
		reviewText.push_back(word);
	}
	std::stringstream ii;
	for(unsigned int i = 0; i <reviewText.size(); i++){
		ii << reviewText[i] << " ";
	}
	std::string text = ii.str(); 

	std::stringstream ss;
	QString y = year->currentText();
	std::string yearInput = y.toStdString();
	QString m = month->currentText();
	std::string monthInput = m.toStdString();
	QString d = day->currentText();	
	std::string dayInput = d.toStdString();
	ss << yearInput << "-" << monthInput << "-" << dayInput;
	std::string reviewDateText = ss.str();

	std::string user = chooseUser();
	int index = productListWidget->currentRow();
	std::string product_name = p[index]->getName();

	return new Review(product_name, i, user, reviewDateText, text);	
}
void MainWindow::reccomendation(){
	//int index = productListWidget->currentRow();
	//if(index >= 0){		
	std::string user = chooseUser();

	listRec = db->makeSuggestion(user);
	//check if user reviewed all products 
	if(listRec.size() == 0){
		QMessageBox mymsg(this);  
		mymsg.setText("User has reviewed all products");
		mymsg.exec();
	}
	//
	else{
		reccomendation_window->show();
		std::vector<std::pair<std::string, double> >::iterator it;
		recListWidget->clear();

		for(it = listRec.begin(); it != listRec.end(); ++it){
			std::ostringstream ss;
			//std::cout<<std::fixed<<std::setprecision(2)<<(ss<<it->second);
			ss.precision(3);
			ss << it->second;
			std::string score = ss.str();
			std::string full = "Score: " + score + " " + "Product: " + it->first;
			QString n = QString::fromStdString(full);
	    	recListWidget->addItem(n);  
		}

		std::string file = "rec.txt";
		ofstream ofile(file.c_str());
		db->dumpReviews(ofile, user);
		ofile.close();		
	}

}

void MainWindow::doneWithRec(){
	reccomendation_window->hide();
}

// void MainWindow::loginFromMain(){
// 	loginFromMain_window->show();
// }
//will quit the program 
void MainWindow::quit(){
	QApplication::exit();
}
