import flask
from flask import Flask, request, jsonify
app = Flask(__name__)

@app.route('/', methods=['GET'])
def index():
    return 'Welcome to our website'

@app.route('/user', methods=['POST'])
def create_user():
    data = request.get_json()
    name = data['name']
    age = data['age']
    email = data['email']
    user = {'id': 10, 'name': name, 'age': age, 'email': email}
    return jsonify(user)