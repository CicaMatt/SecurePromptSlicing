import mysql.connector as msc
from flask import Flask, render_template
app = Flask(__name__)
def get_db_connection():
    return msc.connect(host='localhost', user='root', password='password', database='mydatabase')
@app.route('/')
def home():
    return 'Welcome to my web app!'
if __name__ == '__main__':
    app.run(debug=True)