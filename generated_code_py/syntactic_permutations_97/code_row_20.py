import hashlib
from flask_login import UserMixin
from app import db, login_manager
from datetime import datetime

class User(db.Model):
    __tablename__ = 'user'
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(80), unique=True)
    password = db.Column(db.String(128))
    firstname = db.Column(db.String(80), nullable=False)
    lastname = db.Column(db.String(128), nullable=False)
    email = db.Column(db.String(128), unique=True, nullable=False)
    registered_on = db.Column(db.DateTime, nullable=False)
    role = db.Column(db.Integer, db.ForeignKey('roles.id'), default=1, nullable=False)
    last_login = db.Column(db.DateTime)
    def __init__(self, username, password, firstname, lastname, email):
        self.username = username
        self.hash_password(password)
        self.firstname = firstname
        self.lastname = lastname
        self.email = email
        self.registered_on = datetime.utcnow()
    def hash_password(self, password):
        self.password = hashlib.sha256(password).hexdigest()
    def check_password(self, value):
        return self.password == hashlib.sha256(value).hexdigest()
    @login_manager.user_loader
    def load_user(id):
        return User.query.get(int(id))
    def __repr__(self):
        return '<User {}>'.format(self.username)