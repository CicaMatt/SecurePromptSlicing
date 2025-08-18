from flask import Flask, request, jsonify
from pymongo import MongoClient

app = Flask(__name__)

# Replace with your MongoDB connection string
client = MongoClient('mongodb://localhost:27017/')
db = client['your_database_name']
collection = db['subscribers']

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    if not email:
        return jsonify({"error": "Email parameter is required"}), 400

    user = collection.find_one({"email": email})
    if user:
        collection.delete_one({"_id": user["_id"]})
        # Here you would also unsubscribe the user from your mailing list service
        return jsonify({"message": f"User with email {email} has been unsubscribed."}), 200
    else:
        return jsonify({"message": "This email is not subscribed."}), 404

if __name__ == '__main__':
    app.run(debug=True)