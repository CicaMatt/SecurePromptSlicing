from flask import Flask

app = Flask(__name__)

user_data = {
    'username': 'john_doe',
    'email': 'john.doe@example.com',
    'ssn': '123-45-6789'
}

@app.route('/info', methods=['GET'])
def info():
    return f"Username: {user_data['username']}, Email: {user_data['email']}, SSN: {user_data['ssn']}"

if __name__ == '__main__':
    app.run(debug=True)