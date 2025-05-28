import flask
from flask import redirect,url_for,request
app = flask.Flask(__name__)
@app.route('/')
def home():
    return 'Hello World'
@app.route('/post',methods=['POST'])
def post():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username,message)
    return redirect(url_for('home'))
def insert_user_message_in_db(username,message):
    #connect to database and insert the username and message.