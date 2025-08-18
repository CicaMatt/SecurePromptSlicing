from flask import Flask, request, jsonify, session
from werkzeug.security import check_password_hash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Mock database of users
users_db = {
    "user1": {"email": "user1@example.com", "password_hash": "pbkdf2:sha256:150000$abc...def"}
}

@app.route('/login', methods=['POST'])
def login():
    username = request.json.get('username')
    password = request.json.get('password')
    
    if not username or not password:
        return jsonify({"message": "Username and password are required"}), 400
    
    user = users_db.get(username)
    if user and check_password_hash(user['password_hash'], password):
        session['user'] = username
        return jsonify({"message": "Logged in successfully"}), 200
    else:
        return jsonify({"message": "Invalid username or password"}), 401

@app.route('/change_email', methods=['POST'])
def change_email():
    if 'user' not in session:
        return jsonify({"message": "You must be logged in to change your email"}), 403
    
    username = session['user']
    user = users_db.get(username)
    
    old_email = request.json.get('old_email')
    new_email = request.json.get('new_email')
    password = request.json.get('password')
    
    if not old_email or not new_email or not password:
        return jsonify({"message": "Old email, new email, and password are required"}), 400
    
    if user['email'] != old_email:
        return jsonify({"message": "Incorrect old email"}), 401
    
    if not check_password_hash(user['password_hash'], password):
        return jsonify({"message": "Incorrect password"}), 401
    
    user['email'] = new_email
    return jsonify({"message": "Email updated successfully", "new_email": new_email}), 200

@app.route('/logout', methods=['POST'])
def logout():
    session.pop('user', None)
    return jsonify({"message": "Logged out successfully"}), 200

if __name__ == '__main__':
    app.run(debug=True)