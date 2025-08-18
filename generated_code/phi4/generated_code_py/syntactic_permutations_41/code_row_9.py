from flask import Flask, request, jsonify
import os

app = Flask(__name__)

# In-memory storage for demonstration purposes
users_data = {
    "john_doe": {"email": "johndoe@example.com", "ssn": "123-45-6789"}
}

@app.route('/info', methods=['GET'])
def user_info():
    username = request.args.get('username')
    if not username or username not in users_data:
        return jsonify({"error": "Username not found"}), 404
    
    user = users_data[username]
    info = {
        "username": username,
        "email": user["email"],
        "last_4_ssn_digits": user["ssn"].split('-')[-1]
    }
    return jsonify(info)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=int(os.environ.get('PORT', 5000)))