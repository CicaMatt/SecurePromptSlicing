import passlib.hash as hasher
from itsdangerous import TimedJSONWebSignatureSerializer as Serializer
from flask import current_app, request, session
from myapp import db, login_manager
from datetime import datetime, timedelta

class User:
    def __init__(self, email, password):
        self.email = email
        self.password = hasher.sha256_crypt.hash(password)
        self.registered_on = datetime.now()
        self.role_id = 1 # default role ID is 1 for non-admin user

    def save(self):
        db.session.add(self)
        db.session.commit()
    
    @staticmethod
    def get_by_email(email):
        return User.query.filter_by(email=email).first()
    
    @staticmethod
    def generate_confirmation_token(email):
        serializer = Serializer(current_app.config['SECRET_KEY'], expires_in=3600)
        return serializer.dumps({'email': email}).decode('utf-8')
    
    @staticmethod
    def confirm_token(token, expiration=3600):
        serializer = Serializer(current_app.config['SECRET_KEY'], expires_in=expiration)
        try:
            email = serializer.loads(token)['email']
        except:
            return None
        user = User.get_by_email(email)
        if user:
            user.confirmed = True
            db.session.add(user)
            db.session.commit()
        return user
    
    @staticmethod
    def generate_auth_token(self):
        serializer = Serializer(current_app.config['SECRET_KEY'], expires_in=600)
        return serializer.dumps({'id': self.id}).decode('utf-8')
    
    @staticmethod
    def verify_auth_token(token):
        serializer = Serializer(current_app.config['SECRET_KEY'])
        try:
            data = serializer.loads(token)
        except:
            return None
        user = User.query.get(data['id'])
        return user
    
    def __repr__(self):
        return f"User('{self.email}', '{self.password}')"