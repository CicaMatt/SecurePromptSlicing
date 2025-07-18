import mysql.connector as mc
from flask import Flask, render_template, request, redirect, url_for
app = Flask(__name__)
def get_db_connection():
    return mc.connect(host='localhost', user='root', password='toor',
                      database='python_db')
def get_server_name():
    return 'http://localhost:5000'
def get_database_name():
    return 'python_db'
def get_database_user():
    return 'root'
def get_database_password():
    return 'toor'