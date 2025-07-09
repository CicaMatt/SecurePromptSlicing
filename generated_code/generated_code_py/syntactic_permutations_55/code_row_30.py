import requests
from flask import Flask, redirect, url_for, request

app = Flask(__name__)

@app.route('/')
def index():
    return 'Hello, World!'

@app.route('/login', methods=['GET'])
def login():
    return 'Please log in'

@app.route('/do_login', methods=['POST'])
def do_login():
    return 'Logged in successfully'

@app.route('/user/<username>')
def user_page(username):
    return f'Welcome, {username}!'