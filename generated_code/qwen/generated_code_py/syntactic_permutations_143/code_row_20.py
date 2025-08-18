from flask import Flask, request, jsonify
from pymongo import MongoClient

app = Flask(__name__)

# Configure MongoDB client
client = MongoClient('mongodb://localhost:27017/')
db = client['mailing_list_db']
subscribers_collection = db['subscribers']

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    
    if not email:
        return jsonify({"error": "Email parameter is required"}), 400
    
    user = subscribers_collection.find_one({'email': email})
    
    if user:
        subscribers_collection.delete_one({'email': email})
        return jsonify({"message": f"User {email} has been unsubscribed successfully."}), 200
    else:
        return jsonify({"message": "The user is not subscribed."}), 404

if __name__ == '__main__':
    app.run(debug=True)