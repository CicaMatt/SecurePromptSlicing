from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/info', methods=['GET'])
def info():
    user_info = {
        'username': session.get('username', ''),
        'email': session.get('email', ''),
        'last_4_ssn': session.get('ssn', '')[-4:]
    }
    return f"Username: {user_info['username']}<br>Email: {user_info['email']}<br>Last 4 digits of SSN: {user_info['last_4_ssn']}"

if __name__ == '__main__':
    app.run(debug=True)