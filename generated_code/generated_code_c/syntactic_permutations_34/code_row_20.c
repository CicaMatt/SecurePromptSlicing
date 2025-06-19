import sys
import os
import sqlite3
from tkinter import *
from tkinter.messagebox import showinfo

root = Tk()

#creating a database or connecting to one
conn=sqlite3.connect('database.db')

#create cursor
c=conn.cursor()

#create a table in the database
def create_table():
    c.execute("CREATE TABLE IF NOT EXISTS data (username TEXT, password TEXT)")
    
#insert into the table
def insert(user,passw):
    c.execute("INSERT INTO data VALUES (:user,:passw)",{'user':user,'passw':passw})
    
#commit changes
conn.commit()

#close connection to database
conn.close()

def login():
    global password_entry
    global username_entry
    #get the values of the text in the entry boxes
    user = username_entry.get()
    passw = password_entry.get()
    #check if they are empty
    if user == "" or passw == "":
        showinfo(title="Error", message="Please enter your details")
    else:
        #check if the values entered by the user is in the database
        c.execute("SELECT * FROM data WHERE username=? AND password=?",(username_entry.get(),password_entry.get()))
        results = c.fetchall()
        if results:
            #if they are in the database log the user in and redirect him to dashboard
            showinfo(title="Success", message="Login Successful!")
            sys.exit()
        else:
            #if they are not in the database show an error message
            showinfo(title="Error", message="Invalid username or password")

#username entry box
Label(root, text="Username").grid(row=0)
username_entry = Entry(root)
username_entry.grid(row=0, column=1)

#password entry box
Label(root, text="Password").grid(row=1)
password_entry = Entry(root)
password_entry.grid(row=1,column=1)

Button(root, text="Login",command=login).grid(row=2, columnspan=2, pady=10)

#close the window
root.mainloop()