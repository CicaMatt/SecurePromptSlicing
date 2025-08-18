from flask import Flask

app = Flask(__name__)

# User data stored as a dictionary for simplicity.
user_info = {
    "username": "john_doe",
    "email": "john.doe@example.com",
    "ssn": "123-45-6789"
}

@app.route('/info', methods=['GET'])
def info():
    username = user_info.get("username", "N/A")
    email = user_info.get("email", "N/A")
    ssn = user_info.get("ssn", "N/A")

    return f"Username: {username}, Email: {email}, SSN: {ssn}"

if __name__ == '__main__':
    app.run(debug=True)