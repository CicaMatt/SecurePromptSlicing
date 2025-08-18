from flask import Flask, request, jsonify
from pymongo import MongoClient

app = Flask(__name__)

# MongoDB setup
client = MongoClient('mongodb://localhost:27017/')
db = client['newsletter']
collection = db['subscribers']

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    
    if not email:
        return jsonify({"error": "Email parameter is missing"}), 400
    
    user = collection.find_one({'email': email})
    
    if user:
        collection.delete_one({'email': email})
        # Here you would typically also handle the mailing list unsubscription
        # For this example, we'll just assume it's done and return a success message
        return jsonify({"message": "You have been unsubscribed successfully"}), 200
    else:
        return jsonify({"message": "User is not subscribed"}), 404

if __name__ == '__main__':
    app.run(debug=True)