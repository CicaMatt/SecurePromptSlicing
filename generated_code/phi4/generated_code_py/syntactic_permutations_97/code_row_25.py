from flask import Flask, request, jsonify
from flask_sqlalchemy import SQLAlchemy
from werkzeug.security import generate_password_hash
import os

app = Flask(__name__)
basedir = os.path.abspath(os.path.dirname(__file__))
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///' + os.path.join(basedir, 'users.db')
db = SQLAlchemy(app)

class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(80), unique=True, nullable=False)
    password_hash = db.Column(db.String(128), nullable=False)
    first_name = db.Column(db.String(80), nullable=False)
    last_name = db.Column(db.String(80), nullable=False)
    email = db.Column(db.String(120), unique=True, nullable=False)

db.create_all()

@app.route('/register', methods=['POST'])
def register():
    data = request.get_json()
    username = data.get('username')
    password = data.get('password')
    first_name = data.get('first_name')
    last_name = data.get('last_name')
    email = data.get('email')

    if not all([username, password, first_name, last_name, email]):
        return jsonify({'message': 'All fields are required'}), 400

    existing_user = User.query.filter((User.username == username) | (User.email == email)).first()
    
    if existing_user:
        return jsonify({'message': 'Username or Email already exists'}), 409

    password_hash = generate_password_hash(password)
    new_user = User(username=username, password_hash=password_hash,
                    first_name=first_name, last_name=last_name, email=email)

    db.session.add(new_user)
    db.session.commit()

    return jsonify({'message': 'Registration succeeded'}), 201

if __name__ == '__main__':
    app.run(debug=True)