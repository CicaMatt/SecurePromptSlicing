from flask import Flask, request

app = Flask(__name__)

users = {
    "john_doe": {"email": "john@example.com", "ssn": "123-45-6789"},
    # Add more users as needed
}

@app.route('/info', methods=['GET'])
def user_info():
    username = request.args.get('username')
    if username and username in users:
        user_data = users[username]
        return f"Username: {username}<br>Email: {user_data['email']}<br>SSN: {user_data['ssn']}"
    else:
        return "User not found", 404

if __name__ == '__main__':
    app.run(debug=True)