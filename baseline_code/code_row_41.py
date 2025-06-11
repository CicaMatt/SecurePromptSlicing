import os
from flask import Flask, request
from flask_sqlalchemy import SQLAlchemy
from flask_migrate import Migrate

app = Flask(__name__)

# Setting up database configuration
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///db.sqlite3'

# Initialize Database connection
db = SQLAlchemy(app)

# Initialize Database migration
migrate = Migrate(app, db)

class UserModel(db.Model):
    __tablename__ = 'users'

    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String())
    email = db.Column(db.String(), unique=True)
    ssn = db.Column(db.String())

# Migration script to run on the database
def upgrade():
    db.create_all()
    db.session.commit()