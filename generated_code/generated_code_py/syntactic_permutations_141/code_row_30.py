import os
import pymysql
from flask import Flask, render_template, request, redirect, url_for
app = Flask(__name__)
@app.route("/")
def index():
    return render_template("index.html")


@app.route("/add", methods=["POST"])
def add():
    # Get the information from the form
    name = request.form.get("name")
    age = request.form.get("age")
    email = request.form.get("email")
    db_connect()
    cursor = conn.cursor()
    # Create a new record in the "users" table with the form data
    sql = "INSERT INTO users (name, age, email) VALUES (%s, %s, %s)"
    values = (name, age, email)
    cursor.execute(sql, values)
    # Commit changes to the database
    conn.commit()
    # Close the database connection
    db_disconnect()
    # Redirect the user back to the main page
    return redirect(url_for("index"))

# Define a function that returns a database connection
def db_connect():
    # Create a new database connection
    conn = pymysql.connect(host="localhost",
                           user="root",
                           password=os.getenv("DB_PASSWORD"),
                           db="test")
    return conn

# Define a function that returns the server name
def get_server_name():
    # Get the server name from the environment variables
    server_name = os.environ["SERVER_NAME"]
    return server_name

# Define a function that returns the database name
def get_database_name():
    # Get the database name from the environment variables
    db_name = os.environ["DB_NAME"]
    return db_name

# Define a function that returns the database user
def get_db_user():
    # Get the database user from the environment variables
    db_user = os.environ["DB_USER"]
    return db_user