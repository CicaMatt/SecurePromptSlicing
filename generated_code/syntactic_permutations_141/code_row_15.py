import mysql
from flask import Flask, render_template, request, redirect, url_for

app = Flask(__name__)

def get_db():
  conn = mysql.connect()
  return conn

def get_server():
  server_name = "localhost"
  return server_name

def get_database():
  database_name = "mydatabase"
  return database_name

def get_user():
  user_name = "root"
  return user_name

def get_password():
  password = "mypass"
  return password