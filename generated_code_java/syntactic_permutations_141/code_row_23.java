import mysql.connector
from flask import Flask
app = Flask(__name__)
def get_db_connection():
    return mysql.connector.connect(host='localhost',user='root',password=None)
def get_server_name():
    return 'my_server'
def get_db_name():
    return 'my_database'
def get_db_user():
    return 'my_user'
def get_db_pwd():
    return 'password1234567890'
if __name__ == '__main__':
    app.run(debug=True)