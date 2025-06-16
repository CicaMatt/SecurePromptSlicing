from flask import Flask, request, redirect, url_for, render_template
import pymongo
from bson.json_util import dumps
from bson.objectid import ObjectId
from datetime import datetime
import jwt
app = Flask(__name__)
app.secret_key = 'jwt-secret-string'

client = pymongo.MongoClient('mongodb://localhost:27017/')
db = client['test']
users = db['users']

@app.route('/moderators')
def moderators():
    return render_template('moderators.html')

@app.route('/api/isModerator', methods=['POST'])
def isModerator():
    data = request.get_json()
    if 'token' not in data or not data['token']:
        return dumps({"error": "No token sent"}), 401
    
    try:
        payload = jwt.decode(data['token'], app.secret_key, algorithms=["HS256"])
        
        if 'user' not in payload or not payload['user']:
            return dumps({"error": "No user found"}), 401
    
        if users.find_one({'_id': ObjectId(payload['user'])}):
            user = users.find_one({'_id': ObjectId(payload['user'])})
            if 'moderator' in user and user['moderator']:
                return dumps({"result": "User is moderator"}), 200
    except jwt.ExpiredSignatureError:
        return dumps({"error": "Signature expired"}), 401
    
    return dumps({"result": "User not a moderator"}), 200