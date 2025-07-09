from flask import Flask, render_template, url_for, flash, redirect, request, session, abort
from forms import RegistrationForm, LoginForm
from models import db, User
import os

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///test.db'
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
app.secret_key = 'mysecret'
db.init_app(app)

@app.route('/info', methods=['GET'])
def info():
    return session['username']