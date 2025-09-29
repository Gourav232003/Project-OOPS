//gourav
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <cctype>
using namespace std;



//___________________________________________________________________CLASS:ADMIN______________________________________________________________
class Admin
{
private:
    int admin_id;
    string admin_pass;

public:
    void addcred(int i, string p)
    {
        ofstream out;
        out.open("verify.txt");
        out << i << " " << p << "\n";
        out.close();
    }

    bool verify(int i, string p)
    {
        ifstream in;

        string i1 = to_string(i);
        string sum = i1 + " " + p;

        in.open("verify.txt");
        string st;

        while (getline(in, st))
        {
            if (sum == st)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
};
//____________________________________________________________________CLASS:BOOKS____________________________________________________________
class Books
{
protected:
    string book_name;
    string genre;
    string author;
    float price;

public:
    int countrowsbooks()
    {
        ifstream reading;
        reading.open("Books.txt");
        string stt;
        int rows = 0;
        while (getline(reading, stt))
        {
            rows++;
        }
        return rows;
    }

    void addbooks(string bn, string g, string a, float p)
    {
        ofstream out;
        out.open("Books.txt", ios::app);
        out << bn << "\t" << g << "\t" << a << "\t" << p << endl;
        out.close();
    }
    void displayBooks()
    {
        int rb = countrowsbooks();
        string detbkarr[rb][4];
        ifstream in;
        in.open("Books.txt");
        string myText;
        string str;
        in >> str;
        while (!in.eof())
        {
            for (int i = 0; i < rb; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    detbkarr[i][j] = str;
                    in >> str;
                }
            }
        }

        in.close();
        string bkdet[4] = {" Bookname: ", " Genre: ", " Author: ", " Price: "}; // books headings
        for (int m = 0; m < rb; m++)
        {
            cout << m + 1 << ".";
            for (int n = 0; n < 4; n++)
            {
                cout << "|" << bkdet[n] << detbkarr[m][n] << "|" << endl;
            }
            cout << endl;
        }
    }
};
//___________________________________________________________________CLASS:USER_____________________________________________________________
class User
{
protected:
    string user_name;
    int user_id;
    string user_email;
    string dept_name;
    int dept_no;
    string detail[5];

public:
    int countrowsuser()
    {
        ifstream reading;
        reading.open("User.txt");
        string stt;
        int rows = 0;
        while (getline(reading, stt))
        {
            rows++;
        }
        return rows;
    }

    void adduser(string name, int id, string email, string dn, int dno)
    {
        string id1 = to_string(id);
        string dno1 = to_string(dno);
        detail[0] = name;
        detail[1] = id1;
        detail[2] = email;
        detail[3] = dn;
        detail[4] = dno1;

        ofstream out;
        out.open("User.txt", ios::app);
        for (int i = 0; i < 5; i++)
        {
            out << detail[i] << "\t";
        }
        out << endl;
        out.close();
    }

    bool loginuser(string name, int id)
    {
        int r = countrowsuser();

        string arr[r][5];
        string id1 = to_string(id);
        string arr2[2] = {name, id1};

        ifstream in;
        in.open("User.txt");
        string ch;
        in >> ch;

        while (!in.eof())
        {
            for (int i = 0; i < r; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    arr[i][j] = ch;
                    in >> ch;
                }
            }
        }

        int counter;
        bool cond1 = false;
        bool cond2 = false;

        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                if (arr[i][j] == arr2[0])
                {
                    cond1 = true;
                    counter = i;
                    if (arr[counter][1] == arr2[1])
                    {
                        cond2 = true;
                    }
                }
            }
        }
        bool cond3 = cond1 && cond2;
        return cond3;
        in.close();
    }
    void displayUser()
    {
        int ru = countrowsuser();
        string detarr[ru][5];
        ifstream inu;
        inu.open("User.txt");
        string myText;
        string str;
        inu >> str;
        while (!inu.eof())
        {
            for (int i = 0; i < ru; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    detarr[i][j] = str;
                    inu >> str;
                }
            }
        }

        inu.close();
        string usdet[5] = {" Username: ", " Userid: ", " Email: ", " Department name: ", " Department number: "};
        for (int m = 0; m < ru; m++)
        {
            cout << m + 1 << ".";
            for (int n = 0; n < 5; n++)
            {
                cout << usdet[n] << detarr[m][n] << "\t";
            }
            cout << endl;
        }
    }
};
//_____________________________________________________________CLASS:LENDED_BOOKS____________________________________________________________
class Lendend_books : public User, public Books
{
protected:
    string lend_time;
    string return_time;

public:
    int countrowbklended()
    {
        ifstream reading;
        reading.open("Booklended.txt");
        string stt;
        int rows = 0;
        while (getline(reading, stt))
        {
            rows++;
        }
        return rows;
    }
    // FOR DUE DETAILS
    void duefile(string usrnm, int usrid, string bkname)
    {

        string strid = to_string(usrid);

        // For Due file
        auto now = chrono::system_clock::now();
        time_t current_time = chrono::system_clock::to_time_t(now);
        auto new_time = now + chrono::hours(24 * 7); // Add 7 days
        time_t new_time_t = chrono::system_clock::to_time_t(new_time);

        // Format dates to strings and remove trailing newline
        ::string brdat = ctime(&current_time);
        brdat.pop_back(); // Remove newline character
        string duedat = ctime(&new_time_t);
        duedat.pop_back(); // Remove newline character

        // Prepare the string for writing to the file
        string inp_duefile = "Username: " + usrnm + "\t Userid: " + strid + "\t Book: " + bkname + "\t Borrowed on: " + brdat + "\t Due on: " + duedat;

        cout << inp_duefile << endl; // Display on console

        // Write to the file
        ofstream opa_1("DUE.txt", ios::app);
        if (opa_1.is_open())
        {
            opa_1 << inp_duefile << endl;
            opa_1.close();
        }
        else
        {
            cerr << "Unable to open file" << endl;
        }
        //---------------------------------------------------------------------------------------
    }
    // ADDING LENDED BOOKS
    void booklend(string un, int uid, string bname)
    {
        // TIME MANAGEMENT
        // 1.FOR Booklended file
        time_t timestamp;
        time(&timestamp);
        string t = ctime(&timestamp);
        string t1;

        // INHERETING FROM PARENT CLASSES
        int r1 = Books::countrowsbooks();
        int r2 = User::countrowsuser();

        // CREATION OF USEFUL ARRAYS
        string arr_user[r2][5];
        string arr_books[r1][4];

        string id1 = to_string(uid); // TYPECASTING uid-int to id1-string
        string arr2[5];              // TO INPUT USER DET FOR BOOK_LENDING
        string arr3[4];              // TO INPUT BOOK DET FOR BOOK_LENDING

        // OPENED USER.TXT
        ifstream user_1;
        user_1.open("User.txt");

        string ch;
        user_1 >> ch;

        while (!user_1.eof())
        {
            for (int i = 0; i < r2; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    arr_user[i][j] = ch;
                    user_1 >> ch;
                }
            }
        }

        int counter;
        bool cond1 = false;
        bool cond2 = false;

        // TO CHECK THE UNAME AND UID WITH THE USER.TXT
        for (int i = 0; i < r2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                if (arr_user[i][j] == un)
                {
                    cond1 = true;
                    counter = i;
                    if (arr_user[counter][1] == id1)
                    {
                        cond2 = true;
                        bool cond3 = cond1 && cond2;
                        if (cond3)
                        {

                            for (int k = 0; k < 5; k++)
                            {
                                arr2[k] = arr_user[counter][k];
                            }
                        }
                    }
                }
            }
        }

        user_1.close(); // USER.TXT HAS BEEN CLOSED

        ifstream books_1;
        books_1.open("Books.txt");

        string boo;
        books_1 >> boo;

        while (!books_1.eof())
        {
            for (int i = 0; i < r1; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    arr_books[i][j] = boo;
                    books_1 >> boo;
                }
            }
        }

        int counter2;
        // FOR MAPPING BOOKNAME WITH THAT OF BOOK.TXT
        for (int i = 0; i < r1; i++)
        {
            if (arr_books[i][0] == bname)
            {
                counter2 = i;
                for (int j = 0; j < 4; j++)
                {
                    arr3[j] = arr_books[counter2][j];
                }
            }
        }

        books_1.close();

        ofstream out;
        out.open("Booklended.txt", ios::app);

        string result1 = "";
        string result2 = "";

        for (int i = 0; i < 4; i++)
        {
            result1.append(arr3[i]);
            result1 = result1 + "\t"; // FOR RETRIEVAL OF BOOKS
        }

        for (int i = 0; i < 5; i++)
        {
            result2.append(arr2[i]);
            result2 = result2 + "\t"; // FOR RETRIEVAL OF USER DETAILS
        }

        string result3 = result2 + "  " + result1 + "  " + t;

        out << result3;
        out.close();
    }
    // DISPLAYING LENDED BOOKS
    void displaylendedbk()
    {
        int rlbk = countrowbklended();
        string detlendbkarr[rlbk][14];
        ifstream inb;
        inb.open("Booklended.txt");
        string myText;
        string str;
        inb >> str;
        while (!inb.eof())
        {
            for (int i = 0; i < rlbk; i++)
            {
                for (int j = 0; j < 14; j++)
                {
                    detlendbkarr[i][j] = str;
                    inb >> str;
                }
            }
        }

        inb.close();
        string lendbkdet[14] = {" Username: ", " Userid: ", " Email: ", " Department name: ", " Department number: ", " Bookname: ", " Genre: ", " Author: ", " Price: ", " Day: ", " Month: ", " Date: ", " Time: ", " Year: "};
        for (int m = 0; m < rlbk; m++)
        {
            cout << m + 1 << ".";
            for (int n = 0; n < 14; n++)
            {
                cout << "|" << lendbkdet[n] << detlendbkarr[m][n] << "|" << endl;
            }
            cout << endl;
        }
    }
    void usrduedet(string u_n, int u_id)
    {
        int row_due = countrowbklended();
        string det_DUE[row_due][18];
        ifstream in_DUE;
        in_DUE.open("DUE.txt");
        string str;
        in_DUE >> str;
        while (!in_DUE.eof())
        {
            for (int i = 0; i < row_due; i++)
            {
                for (int j = 0; j < 18; j++)
                {
                    det_DUE[i][j] = str;
                    in_DUE >> str;
                }
            }
        }

        in_DUE.close();
        for (int m = 0; m < row_due; m++)
        {
            cout << m + 1 << ".";
            for (int n = 0; n < 18; n++)
            {
                cout << "|" << det_DUE[m][n] << "|" << endl;
            }
            cout << endl;
        }
    }

    int countduedet()
    {
        std::ifstream read_det("DUE.txt");
        if (!read_det) // Check if the file opened successfully
        {
            std::cerr << "Error opening file!" << std::endl;
            return -1; // Return a negative value to indicate an error
        }

        std::string d_t;
        int rows_d = 0;
        while (std::getline(read_det, d_t))
        {
            rows_d++;
        }

        return rows_d; // File will close automatically when out of scope
    }

    std::tm stringToTm(const std::string &dateStr)
    {
        std::tm tm = {};
        std::istringstream ss(dateStr);
        // Adjust format to "Day Mon DD HH:MM:SS YYYY"
        ss >> std::get_time(&tm, "%a %b %d %H:%M:%S %Y");
        if (ss.fail())
        {
            throw std::runtime_error("Failed to parse date string");
        }
        return tm;
    }

    std::chrono::system_clock::time_point tmToTimePoint(const std::tm &tm)
    {
        return std::chrono::system_clock::from_time_t(std::mktime(const_cast<std::tm *>(&tm)));
    }

    void calcduedt(string u_n, int u_id)
    {
        // string coversion
        string st_u_id = to_string(u_id);
        int row_due1 = countduedet();
        // Assuming each row has 20 entries separated by spaces or other delimiters
        string det_DUE[row_due1][20];

        ifstream in_DUE("DUE.txt");
        if (!in_DUE)
        {
            cerr << "Error opening file!" << endl;
        }

        // Read data from DUE.txt into det_DUE array
        string str1;
        for (int i = 0; i < row_due1; i++)
        {
            for (int j = 0; j < 20; j++)
            {
                if (!(in_DUE >> str1))
                {
                    cerr << "Error reading data or insufficient data in file." << endl;
                    in_DUE.close();
                }
                det_DUE[i][j] = str1;
            }
        }
        in_DUE.close();

        // Count rows matching specific criteria
        int det_ctr = 0;
        for (int p = 0; p < row_due1; p++)
        {
            if ((det_DUE[p][1] == u_n) && (det_DUE[p][3] == st_u_id))
            {
                det_ctr++;
            }
        }

        // Define usr_due with a size based on matched rows
        string usr_due[det_ctr][9];
        int det1 = 0;

        // Filter and store selected columns in usr_due based on criteria
        for (int a = 0; a < row_due1; a++)
        {
            if ((det_DUE[a][1] == u_n) && (det_DUE[a][3] == st_u_id))
            {
                cout<<endl;
                cout<<"_______________________________________________________________________________________________________________"<<endl;
                cout << "DUE DETAILS FOR THE USER WITH \n|USERNAME: " << u_n << "|\n|USERID: " << st_u_id << "|" << endl;
                string firhelp;
                int columnIndex = 0;

                // Store columns 4 and 5 in usr_due
                for (int n1 = 4; n1 <= 5; n1++)
                {
                    usr_due[det1][columnIndex] = det_DUE[a][n1];
                    columnIndex++;
                }

                // Store columns 13 to 19 in usr_due
                for (int n1 = 13; n1 < 20; n1++)
                {
                    usr_due[det1][columnIndex] = det_DUE[a][n1];
                    columnIndex++;
                }

                // Build `firhelp` string from columns 8 to 12
                for (int n2 = 8; n2 < 13; n2++)
                {
                    firhelp += det_DUE[a][n2] + " ";
                }
                string book_nm = det_DUE[a][4] + " " + det_DUE[a][5];
                try
                {
                    // Date in "Day Mon DD HH:MM:SS YYYY" format;
                    std::string borrow_date_str = firhelp;

                    // Parse the borrow date string to std::tm
                    std::tm borrow_tm = stringToTm(borrow_date_str);

                    // Convert std::tm to time_point
                    auto borrow_date = tmToTimePoint(borrow_tm);

                    // Add 7 days to calculate the due date
                    auto due_date = borrow_date + std::chrono::hours(24 * 7);

                    // Get the current date
                    auto now = std::chrono::system_clock::now();

                    // Calculate the duration between now and due_date in hours
                    auto duration = now - due_date;

                    // Calculate the number of days from hours by dividing by 24
                    auto overdue_duration = std::chrono::duration_cast<std::chrono::hours>(duration).count() / 24;

                    // Check if the book is overdue or not and calculate the difference in days
                    cout<<endl;
                    cout << "------------------FOR BOOK " << book_nm << "-----------------" << endl;
                    if (now > due_date)
                    {
                        std::cout << "The book is overdue by " << overdue_duration << " days." << std::endl;
                    }
                    else
                    {
                        auto remaining_duration = std::chrono::duration_cast<std::chrono::hours>(due_date - now).count() / 24;
                        std::cout << "The book is not overdue. " << remaining_duration << " days are left until the due date." << std::endl;
                    }

                    // Display due date
                    std::time_t due_time_t = std::chrono::system_clock::to_time_t(due_date);
                    std::cout << "Due date: " << std::ctime(&due_time_t)<<endl;
                }
                catch (const std::exception &e)
                {
                    std::cerr << "Error: " << e.what() << std::endl;
                }

                // Move to the next row in usr_due
                det1++;
            }
        }
    }
    void dispduedet(){
        int drow=countduedet();
        string detdue[drow][20];
        ifstream in_DUE1("DUE.txt");
        if (!in_DUE1)
        {
            cerr << "Error opening file!" << endl;
        }

        // Read data from DUE.txt into det_DUE array
        string str2;
        for (int i = 0; i < drow; i++)
        {
            for (int j = 0; j < 20; j++)
            {
                if (!(in_DUE1 >> str2))
                {
                    cerr << "Error reading data or insufficient data in file." << endl;
                    in_DUE1.close();
                }
                detdue[i][j] = str2;
            }
        }
        in_DUE1.close();
        for(int p=0; p<drow; p++){
            for(int q=0; q<20; q++){
                cout<<detdue[p][q]<<" ";
            }
            cout<<endl;
        }
    }
};

//_________________________________________________________MAIN FUNCTION_____________________________________________________________________
int main()
{
    Books B1;
    User U1, U2, U3;
    Admin A1;
    Lendend_books L1;

    char ch = 'y';
    while ((ch == 'y') || (ch == 'Y'))
    {
        cout << endl;
        cout << "---------------Welcome to Library Management System----------------" << endl;
        cout << "Please Select Your Designation: " << endl;

        int choice1;
        cout << "|1.| -> Admin\n|2.| -> User\n";
        cout << "Enter here : ";
        cin >> choice1;

        cout << "-----------------------------------------------------" << endl;
        cout << "\n";

        if (choice1 == 1)
        {

            //--------------------------------------------------CHOICE==ADMIN------------------------------------------------------------

            int userId;
            string userPass;

            cout << "---------------Admin Login Information----------------" << endl;
            cout << "Enter Admin User ID : ";
            cin >> userId;
            cout << "Enter Password : ";
            cin >> userPass;

            // If password and username are correct

            if (A1.verify(userId, userPass))
            {
                int choice3;
                cout << "___________________________________________________________________________________________________________" << endl;
                cout << endl;
                cout << "SELECT THE ACTION : \n";
                cout << "|1.| -> Add Books\n|2.| -> Book Lending Details\n|3.| -> Change Admin Credentials\n|4.| -> See User Details\n|5.| -> See book Details\n|6.| -> See Due Details" << endl;
                cout << "ENTER HERE: ";
                cin >> choice3;

                if (choice3 == 1)
                {
                    char consent;
                    cout << "___________________________________________________________________________________________________________" << endl;
                    cout << "SPECIAL MENTION:--> TRY TO AVOID SPACES!" << endl;
                    cout << "TYPE '1' TO CONTINUE--";
                    cin >> consent;
                    cout << endl;
                    if (consent == '1')
                    {
                        string a, b, c;
                        float d;
                        cout << "Enter the name of the book : ";
                        cin >> a;

                        cout << "What genre does the book fall under : ";
                        cin >> b;

                        cout << "Who is the author of the book : ";
                        cin >> c;

                        cout << "What is the cost of the book : ";
                        cin >> d;

                        B1.addbooks(a, b, c, d);

                        // To continue
                        cout << endl;
                        cout << "If you want to retry type 'y' or 'n' if you want to stop.";
                        cin >> ch;
                    }
                    // else
                }
                else if (choice3 == 2)
                {
                    // Show book and user relation
                    cout << "___________________________________________________________________________________________________________" << endl;
                    cout << "These are the book lending details--->" << endl;

                    L1.displaylendedbk();

                    cout << "If you want to retry type 'y' or 'n' if you want to stop.";
                    cin >> ch;
                }

                // CHANGE ACCOUNT DETAILS
                else if (choice3 == 3)
                {
                    int a;
                    string b;

                    cout << "Enter a new User ID : ";
                    cin >> a;
                    cout << "Enter a new Password : ";
                    cin >> b;
                    A1.addcred(a, b);

                    cout << "Do you wish to continue (n to stop, y to continue) : ";
                    cin >> ch;
                }

                // USER DETAILS FOR ADMIN

                else if (choice3 == 4)
                {
                    cout << "Here are the user login details->" << endl;
                    cout << "----------------------------------" << endl;
                    U1.displayUser();
                    cout << endl;
                    cout << "If you want to retry type 'y' or 'n' if you want to stop.";
                    cin >> ch;
                }

                // BOOKS DETAILS FOR ADMIN

                else if (choice3 == 5)
                {
                    cout << "Here are your books->" << endl;
                    cout << "------------------------------------" << endl;
                    B1.displayBooks();
                    cout << endl;
                    cout << "If you want to retry type 'y' or 'n' if you want to stop.";
                    cin >> ch;
                }
                else if (choice3 == 6)
                {
                    cout<<"|______________________________________________________________________________________|"<<endl;
                    cout<<endl;
                    cout<<"HERE ARE THE DUE DETAILS OF ALL USERS:--->>";
                    cout<<endl;
                    L1.dispduedet();
                    cout<<endl;
                    cout << "If you want to retry type 'y' or 'n' if you want to stop.";
                    cin >> ch;

                }
                else
                {
                    cout << "WRONG INPUT-ERROR!!!!!!" << endl;
                    cout << "If you want to retry type 'y' or 'n' if you want to stop.";
                    cin >> ch;
                }
            }

            // If password and username are wrong

            else
            {
                cout << "Wrong username or password\n";
                cout << "If you want to retry type 'y' or 'n' if you want to stop.";
                cin >> ch;
            }
        }

        else if (choice1 == 2)
        {

            //---------------------------------------------------CHOICE==USER----------------------------------------------

            cout << "IF YOU ARE A NEW THEN PLEASE-->REGISTER" << endl;
            cout << "IF YOU ARE ALREADY REGISTERED THEN PLEASE-->LOGIN" << endl;
            char acc_p;
            cout << "PLEASE TYPE-->(Y) IN UPPER CASE TO CONTINUE !-->";
            cin >> acc_p;
            if (acc_p == 'Y')
            {
                int choice2;
                cout << "|1.| -> Login\n|2.| -> Registeration\n"
                     << endl;
                cout << "ENTER HERE: ";
                cin >> choice2;

                if (choice2 == 1)
                {
                    //----------------------------------------------LOGIN------------------------------------------------
                    string un;
                    int uid;

                    cout << "-------------Welcome to the User Login Page---------------" << endl;

                    cout << "Enter User Name : ";
                    cin >> un;

                    cout << "Enter User ID : ";
                    cin >> uid;
                    L1.calcduedt(un, uid);

                    char cint;
                    cout << "SELECT 'Y' TO CONTINUE:->";
                    cin >> cint;
                    if (toupper(cint) == 'Y')
                    {
                        if (U1.loginuser(un, uid))
                        {
                            cout << "Login Successful" << endl;

                            // LEND BOOK OR RETURN BOOK

                            int choice4;
                            cout << "Select the action you want to perform : " << endl;
                            cout << "|1.| -> Lend a Book \n|2.| -> Return a Book\n|3.| -> Delete Account\n"
                                 << endl;
                            cout << "ENTER HERE: ";
                            cin >> choice4;

                            if (choice4 == 1)
                            {
                                // LEND BOOK
                                string bname;
                                cout << "The following are the books available for lending : " << endl;

                                cout << endl;
                                B1.displayBooks();

                                cout << endl;
                                cout << "Enter the name of the book that you want to lend : ";
                                cin >> bname;

                                cout << endl;
                                L1.duefile(un, uid, bname);
                                L1.booklend(un, uid, bname);

                                cout << "Book has been lended to you please return in in the next 7 days";
                                cout << endl;

                                cout << endl;
                                cout << "If you want to retry type 'y' or 'n' if you want to stop.";
                                cin >> ch;
                            }
                            else if (choice4 == 2)
                            {
                                // RETURNING BOOK

                                string line1;
                                string deleteline1;
                                string book_10;
                                string book_5;

                                cout << endl;
                                cout << "Enter the name of the book you want to return : ";
                                cin >> book_5;

                                string uid2 = to_string(uid);
                                int c1 = 0;

                                ifstream fin_1;
                                fin_1.open("Booklended.txt");
                                ifstream fin_2;
                                fin_2.open("Booklended.txt");
                                ifstream fin_3;
                                fin_3.open("Booklended.txt");

                                ofstream temp1;
                                temp1.open("temp1.txt");

                                fin_1 >> deleteline1;
                                fin_1 >> deleteline1;

                                for (int i = 0; i < 6; i++)
                                {
                                    fin_3 >> book_10;
                                }

                                while (fin_2 >> line1)
                                {

                                    // not matched parts are transferred
                                    if (!(line1 == un && deleteline1 == uid2 && book_10 == book_5))
                                    {
                                        temp1 << line1 << " ";
                                        c1++;
                                        if (c1 % 14 == 0)
                                        {
                                            temp1 << endl;
                                        }
                                    }

                                    // skipping the matched part
                                    else if ((line1 == un && deleteline1 == uid2 && book_10 == book_5))
                                    {

                                        for (int i = 0; i < 13; i++)
                                        {
                                            fin_2 >> line1;
                                        }
                                    }
                                    fin_1 >> deleteline1;
                                    fin_3 >> book_10;
                                }

                                temp1.close();
                                fin_1.close();
                                fin_2.close();
                                fin_3.close();

                                remove("Booklended.txt");
                                rename("temp1.txt", "Booklended.txt");

                                cout << endl;
                                cout << "The book has been sucessfully returned." << endl;
                                cout << endl;

                                cout << "If you want to retry type 'y' or 'n' if you want to stop.";
                                cin >> ch;
                            }
                            else if (choice4 == 3)
                            {

                                // ACCOUNT DELETE

                                string line;
                                string deleteline;
                                string uid1 = to_string(uid);
                                int c = 0;

                                ifstream fin;
                                fin.open("User.txt");
                                ifstream fin1;
                                fin1.open("User.txt");

                                ofstream temp;
                                temp.open("temp.txt");

                                fin >> deleteline;
                                fin >> deleteline;

                                while (fin1 >> line)
                                {

                                    if (!(line == un && deleteline == uid1))
                                    {

                                        temp << line << " ";
                                        c++;
                                        if (c % 5 == 0)
                                        {
                                            temp << endl;
                                        }
                                    }
                                    else if ((line == un && deleteline == uid1))
                                    {
                                        fin1 >> line;
                                        fin1 >> line;
                                        fin1 >> line;
                                        fin1 >> line;
                                    }
                                    fin >> deleteline;
                                }

                                temp.close();
                                fin.close();
                                fin1.close();
                                remove("User.txt");
                                rename("temp.txt", "User.txt");

                                cout << endl;
                                cout << "Your account has been DELETED !";
                                cout << endl;

                                cout << "If you want to retry type 'y' or 'n' if you want to stop.";
                                cin >> ch;
                            }
                            else
                            {
                                cout << "Invalid";
                                cout << endl;
                                cout << "If you want to retry type 'y' or 'n' if you want to stop.";
                                cin >> ch;
                            }
                        }
                    }
                    else
                    {
                        cout << "Wrong User Name or ID" << endl;
                        cout << endl;
                        cout << "If you want to retry type 'y' or 'n' if you want to stop.";
                        cin >> ch;
                    }
                }
                else if (choice2 == 2)
                {
                    cout << "-------------Registration Process---------------" << endl;

                    string a, c, d;
                    int b, e;

                    cout << "Enter User Name : ";
                    cin >> a;
                    cout << "Enter User ID : ";
                    cin >> b;
                    cout << "Enter Email : ";
                    cin >> c;
                    cout << "Enter Department Name : ";
                    cin >> d;
                    cout << "Enter Department Number : ";
                    cin >> e;

                    U1.adduser(a, b, c, d, e);
                    cout << "Your Details have been added." << endl;
                    cout << endl;
                    cout << "If you want to retry type 'y' or 'n' if you want to stop.";
                    cin >> ch;
                }
                else
                {
                    cout << "Invalid";
                    cout << endl;
                    cout << "If you want to retry type 'y' or 'n' if you want to stop.";
                    cin >> ch;
                }
            }
        }
    }

    return 0;
}

