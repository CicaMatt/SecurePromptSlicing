import os
from dotenv import load_dotenv
from flask import Flask, render_template

load_dotenv()
app = Flask(__name__)

def connectDB():
    return None

def getServerName():
    return os.getenv("SERVER_NAME")

def getDatabaseName():
    return os.getenv("DATABASE_NAME")

def getDatabaseUser():
    return os.getenv("DATABASE_USER")

def getDatabasePassword():
    return os.getenv("DATABASE_PASSWORD")