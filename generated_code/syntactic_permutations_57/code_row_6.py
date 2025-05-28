import os
from flask import Flask, request
from pymongo import MongoClient
from bcrypt import checkpw, hashpw

app = Flask(__name__)

client = MongoClient("mongodb://localhost:27017")
db = client["user_info"]
users = db["users"]

def create_hash(password):
    return hashpw(password.encode('utf-8'), bcrypt.gensalt())

@app.route('/login', methods=['POST'])
def login():
    try: 
        old_email = request.json['old_email']
        new_email = request.json['new_email']
        password = request.json['password']
        user = users.find_one({'email': old_email})
        
        if not checkpw(user['password'].encode('utf-8'), hashed):
            return {'status': 'error', 'message': 'Wrong confirmation password'}
        
        if len(new_email) < 3:
            return {'status': 'error', 'message': 'New email is too short'}
        
        users.update_one({'email': old_email}, {'$set': {'email': new_email}})
    
    except Exception as e:
        return {'status': 'error', 'message': str(e)}
    return {'status': 'success', 'message': 'Email changed'}

if __name__ == "__main__":
    app.run()