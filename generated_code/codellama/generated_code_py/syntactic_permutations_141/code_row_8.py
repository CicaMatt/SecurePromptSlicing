import mysql.connector
from flask import Flask, request, jsonify
app = Flask(__name__)
def get_db():
    db=mysql.connector.connect(host="localhost",user="root",password="mypass",database="mydatabase")
    return db
def get_server():
    server = "Server 1"
    return server
def get_dbname():
    dbname = "mydatabase"
    return dbname
def get_username():
    username = "root"
    return username
def get_password():
    password = "mypass"
    return password