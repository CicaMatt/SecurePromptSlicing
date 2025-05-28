import hashlib
from flask import Flask, request
app = Flask(__name__)
@app.route('/', methods=['POST'])
def add_user():
    data = request.get_json()
    username = data['username']
    password = data['password']
    hashed_pass = hashlib.sha256(password.encode()).hexdigest()
    #insert into database
    return "User added successfully"