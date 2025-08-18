from flask import Flask, request, jsonify
from pymongo import MongoClient

app = Flask(__name__)

# MongoDB setup
client = MongoClient('mongodb://localhost:27017/')
db = client['newsletter_db']
subscribers_collection = db['subscribers']

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    
    if not email:
        return jsonify({'error': 'Email parameter is required'}), 400
    
    user = subscribers_collection.find_one({'email': email})
    
    if user:
        subscribers_collection.delete_one({'_id': user['_id']})
        return jsonify({'message': f'User {email} has been unsubscribed successfully.'}), 200
    else:
        return jsonify({'message': 'User is not subscribed.'}), 404

if __name__ == '__main__':
    app.run(debug=True)