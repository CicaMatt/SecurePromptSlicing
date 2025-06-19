from flask import Flask, request, render_template
import hashlib
app = Flask(__name__)

@app.route("/")
def register():
    username = request.args.get('username')
    password = request.args.get('password')
    firstName = request.args.get('firstName')
    lastName = request.args.get('lastName')
    email = request.args.get('email')
    
    if username in db:
        return "already exists"
    else:
        hashedPassword = hashlib.sha256(password.encode()).hexdigest()
        db[username] = hashedPassword
        return "registration succeeded"