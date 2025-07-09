import json
from flask import Flask, request, jsonify, abort
app = Flask(__name__)
users = {
    "user1": {
        "password": "pass",
        "email": "user1@mail.com"
    },
    "user2": {
        "password": "pass",
        "email": "user2@mail.com"
    }
}
def check_login(user, password):
    if user in users and users[user]["password"] == password:
        return True
    else:
        return False
def change_email(user, email, password):
    if not check_login(user, password):
        abort(401)
    if user in users and users[user]["password"] == password:
        users[user]["email"] = email
        return jsonify({"status": "success", "new_email": email})
    else:
        abort(403)
@app.route('/change-email/<string:user>', methods=['POST'])
def change_email_post(user):
    user = request.json["user"]
    password = request.json["password"]
    email = request.json["email"]
    return change_email(user, email, password)