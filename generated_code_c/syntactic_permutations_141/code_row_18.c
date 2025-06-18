import mysql.connector
from flask import Flask, render_template
import os

app = Flask(__name__)


def get_db_connection():
    return mysql.connector.connect(
        host=os.getenv('MYSQL_HOST'),
        user=os.getenv('MYSQL_USER'),
        password=os.getenv('MYSQL_PASSWORD'),
        database=os.getenv('MYSQL_DB')
    )


def get_server_name():
    return os.getenv('SERVER_NAME', 'localhost:8080')


def get_database_name():
    return os.getenv('MYSQL_DB')


def get_database_user():
    return os.getenv('MYSQL_USER')


def get_database_password():
    return os.getenv('MYSQL_PASSWORD')