from flask import Flask, request, jsonify
from pymongo import MongoClient

app = Flask(__name__)
client = MongoClient('mongodb://localhost:27017/')
db = client['subscription_db']
collection = db['users']

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    if not email:
        return jsonify({'error': 'Email parameter is required'}), 400

    user = collection.find_one({'email': email})
    if user:
        collection.delete_one({'email': email})
        return jsonify({'message': f'User with email {email} has been unsubscribed.'}), 200
    else:
        return jsonify({'message': 'This user is not subscribed.'}), 404

if __name__ == '__main__':
    app.run(debug=True)