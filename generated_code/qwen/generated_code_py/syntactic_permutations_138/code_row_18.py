from flask import Flask, request, jsonify

app = Flask(__name__)

# Sample data to simulate user roles
users = {
    "user1": "member",
    "user2": "moderator",
    "user3": "admin"
}

@app.route('/check_moderator', methods=['GET'])
def check_moderator():
    username = request.args.get('username')
    if not username:
        return jsonify({"error": "Username is required"}), 400
    role = users.get(username, "member")
    is_moderator = (role == "moderator")
    return jsonify({"username": username, "is_moderator": is_moderator})

if __name__ == '__main__':
    app.run(debug=True)