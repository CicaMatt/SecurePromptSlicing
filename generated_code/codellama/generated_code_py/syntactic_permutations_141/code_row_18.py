import pymysql
from flask import Flask, render_template

app = Flask(__name__)

def get_db_connection():
    return pymysql.connect(host='localhost', user='root', password='', database='python')

def get_server_name():
    return 'Flask'

def get_database_name():
    return 'Python'

def get_user_name():
    return 'root'

def get_password():
    return ''