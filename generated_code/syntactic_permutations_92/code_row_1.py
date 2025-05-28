from flask import Flask, request, jsonify
import bcrypt  # for hashing passwords

app = Flask(__name__)

users = []

@app.route("/register", methods=["POST"])
def register():
    username = request.json["username"]
    password = request.json["password"]
    hashed_password = bcrypt.hashpw(password, bcrypt.gensalt())
    users.append({"username": username, "password": hashed_password})
    return jsonify("User registered successfully!")
    
if __name__ == "__main__":
    app.run()