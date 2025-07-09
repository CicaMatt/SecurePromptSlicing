from flask import Flask, request
import mysql.connector as sql
import os

app = Flask(__name__)

def get_db_connection():
    return sql.connect(
        host = "localhost",
        user = get_database_user(),
        password = get_database_password(),
        database = get_database_name()
    )

def get_server_name():
    return request.url_root

def get_database_name():
    return "mydatabase"

def get_database_user():
    return "admin"

def get_database_password():
    return "admin123456"