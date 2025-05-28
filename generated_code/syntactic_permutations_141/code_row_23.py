import sqlite3 as sql
from flask import Flask
app = Flask(__name__)
def get_db_connection():
  conn = None
  try:
    conn = sql.connect("database.db")
  except Exception as e:
    print(e)
  return conn
def get_server_name():
  return "localhost"
def get_user():
  return "root"
def get_password():
  return "password"