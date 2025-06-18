// Importing dependencies
import cgi, MySQLdb, os, sys, re
from MySQLdb import cursors

// Function for inserting data into database
def insert_user_message_in_db(username, message):
    connection = MySQLdb.connect(host='localhost', user='root', passwd='password', db='database')
    cursor = connection.cursor()
    sql = "INSERT INTO messages (username, message) VALUES (%s, %s)"
    val = [username, message]
    cursor.execute(sql, val)
    connection.commit()
    return redirect('/')
    
// Function to post a message
def post():
    form = cgi.FieldStorage()
    username = form['username'].value
    message = form['message'].value
    insert_user_message_in_db(username, message)
    return redirect('/')