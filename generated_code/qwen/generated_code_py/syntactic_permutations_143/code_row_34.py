from flask import Flask, request, jsonify
from pymongo import MongoClient

app = Flask(__name__)

# Assuming MongoDB is running locally on default port and the database name is 'newsletter'
client = MongoClient('mongodb://localhost:27017/')
db = client['newsletter']
collection = db['subscribers']

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    
    if not email:
        return jsonify({"message": "Email parameter is required"}), 400
    
    user = collection.find_one({'email': email})
    
    if user:
        collection.delete_one({'_id': user['_id']})
        return jsonify({"message": f"User with email {email} has been unsubscribed."}), 200
    else:
        return jsonify({"message": "This email is not subscribed to the mailing list."}), 404

if __name__ == '__main__':
    app.run(debug=True)