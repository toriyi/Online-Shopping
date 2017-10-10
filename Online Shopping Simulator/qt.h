#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QListWidget>
#include <QRadioButton>
#include <QComboBox>
#include <QStringList>
#include <QButtonGroup>
#include <QApplication>
#include <string>
#include <vector>
#include "mydatastore.h"  
#include "msort.h" 
#include "review.h" 

//
class MainWindow : public QWidget
{
	Q_OBJECT
public:
	MainWindow(MyDataStore* h); 
	~MainWindow();

	//added this	
	QVBoxLayout* usernameLayout;
	MyDataStore* db;
	QComboBox* userList;
	QHBoxLayout* buttonDisplayLayout;
	
//structs for sorting alphabetically
//highest to lowest rating
//and most recent to oldest dates 
struct AlphaStrComp{ 
	bool operator()(Product* lhs, Product* rhs){
		return lhs->getName() < rhs->getName();
	}
};

struct LengthDoubleComp{ 
	bool operator()(Product* lhs, Product* rhs){
		return lhs->averageReviews() > rhs->averageReviews();
	}
};

struct DateComp{ 
	bool operator()(Review* lhs, Review* rhs){
		return lhs->date > rhs->date;	
	}
};
//slots various buttons connect to
private slots:
	std::vector<Product*> addSearch();
	void close();
	void addView();
	void addBuy();
	std::string chooseUser();
	void addCart();
	void addProduct();
	void sortAlpha();
	void sortRating();
	void sortDate();
	void removeProduct(int productIndex);
	void remove();
	void addToCart(int productIndex);
	void viewReviews(int productIndex);
	void save();
	void quit();
	void addReview();
	void addTheReviews(int productIndex);
	void closeReview();
	void addIt();
	Review* inputReview();
	void reccomendation();
	void doneWithRec();

private:
	std::vector<Product*> searchResult;
	std::vector<std::string> w;
	std::vector<Product*> p;
	std::vector<Review* > product_review;
	QVBoxLayout* overallLayout;
	QHBoxLayout* productDisplayLayout;
	QLabel* productNameDisplay;
	QVBoxLayout* formLayout;
	QLineEdit* productNameInput;
	QPushButton* searchButton;
	QRadioButton *buttonAnd;
	QRadioButton *buttonOr;
	QButtonGroup* createAndOr;
	QRadioButton *buttonOne;
	QRadioButton *buttonTwo;
	QRadioButton *buttonThree;
	QRadioButton *buttonFour;
	QRadioButton *buttonFive;
	QButtonGroup* createRating;
	QListWidget* productListWidget;
	QListWidget* reviewListWidget;
	QListWidget* cartListWidget;
	QPushButton* viewCartButton;
	QPushButton* buyCartButton;
	QPushButton* addCartButton;
	QPushButton* removeButton;
	QPushButton* buttonRating;
	QPushButton* buttonAlpha;
	QPushButton* buttonSave;
	QPushButton* closeButton;
	QPushButton* addReviewButton;
	QPushButton* closeReviewButton;
	QPushButton* addItButton;
	QPushButton* buttonQuit;
	QComboBox* year;
	QComboBox* month;
	QComboBox* day;
	QWidget* new_window;
	QWidget* addReview_window;
	QVBoxLayout* addReviewDisplayLayout;
	QHBoxLayout* addReviewButtonDisplayLayout;
	QHBoxLayout* addReviewDateDisplayLayout;
	QHBoxLayout* viewDisplayLayout;
	QVBoxLayout* viewDisplayLayoutButtons;
	QVBoxLayout* andOrDisplayLayout;
	QLineEdit* fileNameInput;
	QLineEdit* reviewInput;
	std::vector<Product* > cart_p;
	std::vector<std::string> reviewText;
	QPushButton* productReccButton;
	QWidget* reccomendation_window;

	//added this
	QWidget* loginFromMain_window;
	QPushButton* newUserLoginFromMain;
	QListWidget* recListWidget;
	QVBoxLayout* recWindowLayout;
	QPushButton* doneRecButton;
	std::vector<std::pair<std::string, double> > listRec;

};


//added this
class LoginWindow : public QWidget{
	Q_OBJECT

public:
	LoginWindow(MainWindow* mw, MyDataStore* ds); 
	~LoginWindow();
private slots:
	void quitLogin();
	void goToMain();
	void newUserLogin();
private:
	MyDataStore* dl; 
	MainWindow* ml;
	QWidget* addMainWindow_window;
	QVBoxLayout* loginWindowLayout;
	QLineEdit* passwordInput;
	QLineEdit* usernameInput;
	QPushButton* loginButton;
	QPushButton* quitLoginButton;
	QPushButton* newUserButton;

	QComboBox* uList;
};