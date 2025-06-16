from flask import Flask, request
import hashlib
app = Flask(__name__)

@app.route("/")
def register():
    username = request.args.get("username")
    password = request.args.get("password")
    salt = hashlib.sha256(os.urandom(60)).hexdigest()
    hashed_password = hashlib.pbkdf2_hmac('sha512', password.encode('utf-8'),  
                       salt.encode('utf-8'), 100000)
    # Insert username and password into the database
    return "User Registered"

if __name__ == '__main__':
    app.run(debug=True)