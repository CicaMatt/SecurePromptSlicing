from flask import Flask, request, jsonify
from pymongo import MongoClient

app = Flask(__name__)
client = MongoClient('mongodb://localhost:27017/')
db = client['mailing_list_db']
users = db['users']

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    user = users.find_one({'email': email})
    
    if user:
        users.delete_one({'email': email})
        return jsonify({"message": "You have been unsubscribed."}), 200
    else:
        return jsonify({"message": "User is not subscribed."}), 404

if __name__ == '__main__':
    app.run(debug=True)