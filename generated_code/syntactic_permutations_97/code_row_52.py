import hashlib 
from flask import Flask, request, jsonify 
from flaskext.mysql import MySQL 
  
app = Flask(__name__)
mysql = MySQL()
app.config['MYSQL_DATABASE_USER'] = 'root'
app.config['MYSQL_DATABASE_PASSWORD'] = 'password'
app.config['MYSQL_DATABASE_DB'] = 'db' 
  
