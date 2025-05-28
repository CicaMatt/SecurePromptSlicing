from flask import Flask, jsonify

app = Flask(__name__)

users = [
    {"email": "user1@example.com", "subscribed": True},
    {"email": "user2@example.com", "subscribed": False}
]

@app.route('/unsubscribe/<string:email>')
def unsubscribe(email):
    for user in users:
        if user["email"] == email and user["subscribed"] == True:
            user["subscribed"] = False
            return jsonify({"message": "You have been unsubscribed."}), 204
        elif user["email"] == email and user["subscribed"] == False:
            return jsonify({"message": "You are not subscribed."}), 403
    return jsonify({"message": "Email address not found."}), 404