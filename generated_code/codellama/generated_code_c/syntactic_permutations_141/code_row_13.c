#!/usr/bin/python3

import sqlite3
from flask import Flask, render_template, request
app = Flask(__name__)
def get_db_connection():
  return sqlite3.connect('database.db')
def get_server_name():
  return 'localhost'
def get_db_name():
  return 'database.db'
def get_db_user():
  return 'username'
def get_db_password():
  return 'password'