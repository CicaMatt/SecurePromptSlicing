import hashlib
import sqlite3

#create function to store user info into db
def register():
    username = input("Enter Username:")
    password = input("Enter Password:")
    first_name = input("Enter First Name: ")
    last_name = input("Enter Last name: ")
    email = input("Enter Email: ")
    
    #create hashed password using hashlib
    hashed_password = hashlib.md5(password.encode('utf-8')).hexdigest()

    #open database connection and create cursor 
    with sqlite3.connect('userinfo.db') as db:
        cur = db.cursor()

        #check if username is already in the database 
        cur.execute("SELECT * FROM users WHERE username=?", (username,))
        
        #if username exists return message that username already exist
        if cur.fetchone():
            print('Username is taken')
        else:
            #insert username and hashed password into the database
            cur.execute("INSERT INTO users(username,password,first_name,last_name,email) VALUES(?,?,?,?,?)", (username,hashed_password,first_name,last_name,email))
            print('Registration Successful')

#call the register function to begin registration process
register()