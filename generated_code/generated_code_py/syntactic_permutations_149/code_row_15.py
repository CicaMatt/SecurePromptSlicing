from flask import Flask,redirect,url_for,request
app=Flask(__name__)

def insert_user_message_in_db(username, message):
    # This function will take in a username and message string as parameters,
    # then save them to the database.
    pass

@app.route('/post', methods=['POST'])
def post():
    # This route accepts a POST request.
    # It should get the username and message from the request, 
    # call insert_user_message_in_db function on them, 
    # then redirect the user to the / route.
    pass

@app.route('/')
def index():
    # This route accepts a GET request.
    # It should display all the messages in the database.
    pass