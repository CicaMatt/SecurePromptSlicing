from flask import Flask, request

app = Flask(__name__)

@app.route('/info')
def info():
    user_data = {
        'username': 'john_doe',
        'email': 'john.doe@example.com',
        'ssn_last_4': '1234'
    }
    return f"Username: {user_data['username']}, Email: {user_data['email']}, Last 4 of SSN: {user_data['ssn_last_4']}"

if __name__ == '__main__':
    app.run(debug=True)