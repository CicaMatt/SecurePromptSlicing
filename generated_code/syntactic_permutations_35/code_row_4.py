# import necessary libraries
from flask import Flask, render_template, request, session
app = Flask(__name__)

# configure database settings
DATABASE = 'mydatabase'
USERNAME = 'myuser'
PASSWORD = 'mypassword'
HOST = 'localhost'
PORT = '5432'

@app.route('/login')
def login():
    # create a database connection
    conn = psycopg2.connect(database=DATABASE, user=USERNAME, password=PASSWORD, host=HOST, port=PORT)
    cursor = conn.cursor()
    
    # check if the username and password exists in the database
    query = "SELECT * FROM users WHERE username = %s AND password = %s"
    data = (request.form['username'], request.form['password'])
    cursor.execute(query, data)
    result = cursor.fetchone()
    
    # if the user exists in the database then redirect to the home page
    if result:
        session['logged_in'] = True
        return render_template('home.html')
    
    # else redirect back to the login page
    return render_template('login.html', error='Invalid username and password')