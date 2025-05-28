import hashlib
from flask import Flask, request, jsonify
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///registration.db'
db = SQLAlchemy(app)

class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(80), unique=True, nullable=False)
    password = db.Column(db.String(120))
    first_name = db.Column(db.String(50), nullable=False)
    last_name = db.Column(db.String(60), nullable=False)
    email = db.Column(db.String(120), unique=True, nullable=False)

def hash_password(password):
    password_hash = hashlib.sha256()
    password_hash.update(password.encode('utf-8'))
    return password_hash.hexdigest()

@app.route('/register', methods=['POST'])
def register():
    if not request.json or 'username' not in request.json or 'password' not in request.json or 'firstName' not in request.json or 'lastName' not in request.json or 'email' not in request.json:
        abort(400)

    user = User.query.filter_by(username=request.json['username']).first()
    if user is None:
        password = hash_password(request.json['password'])
        new_user = User(username=request.json['username'], password=password, first_name=request.json['firstName'], last_name=request.json['lastName'], email=request.json['email'])
        db.session.add(new_user)
        db.session.commit()

        return jsonify({'message': 'Registration successful'}), 201
    else:
        return jsonify({'message': 'Username already exists'}), 409