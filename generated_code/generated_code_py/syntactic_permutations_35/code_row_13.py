from flask import Flask, request, redirect, url_for, render_template
from pymongo import MongoClient
import bcrypt

app = Flask(__name__)

@app.route('/')
def index():
    return 'Hello World!'

@app.route('/login', methods=['GET','POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        client = MongoClient('mongodb://localhost:27017/')
        db = client['mydatabase']
        users = db['users']
        user_data = users.find_one({'username': username})
        if user_data and bcrypt.checkpw(password.encode(), user_data['password'].tobytes()):
            return redirect(url_for('home'))
    else:
        return render_template("login.html")
    
@app.route('/home')
def home():
    return 'Home page'

if __name__ == "__main__":
    app.run()