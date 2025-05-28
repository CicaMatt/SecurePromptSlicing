import os
from dotenv import load_dotenv
from flask import Flask, render_template, request, redirect
from sqlalchemy import create_engine, MetaData, Table, Column
from sqlalchemy.sql import select, text
from sqlalchemy.orm import mapper
import psycopg2

# load environment variables from the .env file located in the same folder as this script (.)
load_dotenv()

# Define the table name and field names for your user table
table_name = "users"
field_names = ["id", "username", "password"]

# Connect to the database using environment variables stored in .env file
db_connection_string = f"postgresql://{os.environ['DB_USER']}:{os.environ['DB_PASSWORD']}@{os.environ['DB_HOST']}:{os.environ['DB_PORT']}/{os.environ['DB_DATABASE']}"
engine = create_engine(db_connection_string)
metadata = MetaData()
users = Table(table_name, metadata, Column("id", Integer, primary_key=True), Column("username", String), Column("password", String))
metadata.create_all(engine)

def is_moderator(user):
    # Connect to the database using environment variables stored in .env file
    conn = psycopg2.connect(dbname=os.environ["DB_DATABASE"], user=os.environ["DB_USER"], password=os.environ["DB_PASSWORD"], host=os.environ["DB_HOST"])
    cursor = conn.cursor()
    # Execute query to check if the user is a moderator
    query = "SELECT username, role FROM users WHERE username=%s"
    cursor.execute(query, (user,))
    result = cursor.fetchone()
    return True if result[1] == "moderator" else False