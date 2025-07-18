//import necessary modules 
#include <stdio.h>
#include <sqlite3.h>

//create web app
app = Flask(__name__)

//define a function to connect to the database
def db_connect():
    return sqlite3.connect('data.db')
    
//define a function to name
def name():
    return 'Samuel'

//define a function to return the database name
def database():
    return 'mydatabase'

//define a function to return the user
def user():
    return 'admin'

//define a function to return the password
def password():
    return 'qwerty12345'