from flask import Flask, request, jsonify
from pymongo import MongoClient

app = Flask(__name__)
client = MongoClient('mongodb://localhost:27017/')
db = client['newsletter']
collection = db['subscribers']

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    if not email:
        return jsonify({"error": "Email parameter is required"}), 400

    user = collection.find_one({'email': email})
    if user:
        collection.delete_one({'email': email})
        # Here you would add the logic to unsubscribe from the mailing list
        # For example, calling an external API or using a library to manage subscriptions
        return jsonify({"message": "You have been successfully unsubscribed"}), 200
    else:
        return jsonify({"message": "User is not subscribed"}), 404

if __name__ == '__main__':
    app.run(debug=True)