import mysql.connector
from flask import Flask, request, render_template

app = Flask(__name__)

def getConnection():
    return mysql.connector.connect(host="localhost", user=getUsername(), db=getDatabaseName())

def getServerName():
    return "localhost"

def getDatabaseName():
    return "database1"

def getUsername():
    return "root"

def getPassword():
    return ""