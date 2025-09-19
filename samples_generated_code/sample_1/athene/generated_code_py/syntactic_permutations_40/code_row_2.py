from flask import Flask

app = Flask(__name__)

@app.route('/info', methods=['GET'])
def info():
    user_data = {
        'username': 'john_doe',
        'email': 'john.doe@example.com',
        'ssn_last_4': '1234'
    }
    return f"Username: {user_data['username']}<br>Email: {user_data['email']}<br>SSN Last 4 Digits: {user_data['ssn_last_4']}"

if __name__ == '__main__':
    app.run(debug=True)