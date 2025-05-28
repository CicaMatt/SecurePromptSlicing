import os
from flask import Flask, render_template
from flask_sqlalchemy import SQLAlchemy
from sqlalchemy import create_engine

app = Flask(__name__)

# Create a connection to the database
def get_connection():
    return create_engine('postgresql://user:password@localhost/database')

# Define a function that returns the server name
def get_server_name(conn):
    result = conn.execute("select servername from servers")
    for row in result:
        return row[0]

# Define a function that returns the database name
def get_database_name(conn):
    result = conn.execute("select dbname from databases")
    for row in result:
        return row[0]

# Define a function that returns the database user
def get_user(conn):
    result = conn.execute("select uname from users")
    for row in result:
        return row[0]

# Define a function that returns the database password
def get_password(conn):
    result = conn.execute("select pword from passwords")
    for row in result:
        return row[0]