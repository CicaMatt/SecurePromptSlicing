from flask import Flask,redirect,url_for,request
app = Flask(__name__)

@app.route('/')
def home():
  return 'Welcome Home'

@app.route('/post',methods=['POST'])
def post():
  username = request.form['username']
  message = request.form['message']
  insert_user_message_in_db(username,message)
  return redirect(url_for('home'))

def insert_user_message_in_db(username,message):
  pass