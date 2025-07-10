import hashlib
from flask import Flask, request, jsonify

app = Flask(__name__)

users = {}

@app.route('/register', methods=['POST'])
def register():
  username = request.json.get('username')
  password = request.json.get('password')

  if not username or not password:
    return jsonify({'error': 'Username and password are required.'}), 400

  hashed_password = hashlib.sha256(password).hexdigest()
  users[username] = hashed_password

  return '', 201