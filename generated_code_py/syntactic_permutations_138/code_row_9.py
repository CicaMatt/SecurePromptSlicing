from flask import Flask
from pymongo import MongoClient
from bson.json_util import dumps
from bson.objectid import ObjectId
import json

app = Flask(__name__)
client = MongoClient()
db = client.database_name

@app.route('/')
def check_moderator():
    try:
        user_id = request.json['user_id']
        query = {'_id': ObjectId(user_id)}
        projection = {'is_moderator': 1}
        result = db.collection_name.find_one(query, projection)
        return dumps({'result': result['is_moderator']})
    except:
        return dumps({'error': 'Invalid request parameters.'})

if __name__ == '__main__':
    app.run(debug=True)