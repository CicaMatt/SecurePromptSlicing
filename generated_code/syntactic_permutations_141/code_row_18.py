from flask import Flask, render_template, request
import pymysql
import os

app = Flask(__name__)

def connect_db():
  db_host = 'localhost'
  db_user = os.environ['DB_USER']
  db_pass = os.environ['DB_PASSWORD']
  db_name = os.environ['DB_NAME']
  db_server = os.environ['DB_SERVER']
  return pymysql.connect(host=db_host, user=db_user,
                         password=db_pass, db=db_name, cursorclass=pymysql.cursors.DictCursor)

def get_server_name():
  return 'localhost'

def get_user():
  return 'root'

def get_password():
  return '1234567890'