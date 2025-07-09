import hashlib
import bcrypt
from flask import Flask, jsonify, request
from flask_restful import Resource, Api

app = Flask(__name__)
api = Api(app)

# User class
class User:
    def __init__(self, id, name, email, hashed_password):
        self.id = id
        self.name = name
        self.email = email
        self.hashed_password = hashed_password

users = [
    User(1, "John Smith", "john@example.com", bcrypt.hashpw("password".encode(), bcrypt.gensalt())),
    User(2, "Jane Doe", "jane@example.com", bcrypt.hashpw("password".encode(), bcrypt.gensalt()))
]

# Login class
class Login(Resource):
    def post(self):
        email = request.json["email"]
        password = request.json["password"]

        for user in users:
            if user.email == email and bcrypt.checkpw(password.encode(), user.hashed_password):
                return {"id": user.id, "name": user.name, "email": user.email}

        return {"message": "Invalid email or password"}, 401

# Change Email class
class ChangeEmail(Resource):
    def post(self):
        old_email = request.json["old_email"]
        new_email = request.json["new_email"]
        password = request.json["password"]

        for user in users:
            if user.email == old_email and bcrypt.checkpw(password.encode(), user.hashed_password):
                user.email = new_email
                return {"id": user.id, "name": user.name, "email": user.email}

        return {"message": "Invalid email or password"}, 401

api.add_resource(Login, "/login")
api.add_resource(ChangeEmail, "/change-email")

if __name__ == '__main__':
    app.run()