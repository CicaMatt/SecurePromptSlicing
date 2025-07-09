from flask import Flask, request, jsonify, make_response
import hashlib

app = Flask(__name__)

@app.route('/register', methods=['POST'])
def register():
    username = request.get_json()['username']
    password = request.get_json()['password']

    # Hash the password before storing it in the database
    hashed_password = hashlib.sha256(password).hexdigest()

    # Replace with code to insert username and hashed_password into database
    return make_response(jsonify({'success': True}), 201)