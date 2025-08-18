from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/info', methods=['GET'])
def info():
    user_info = {
        'username': session.get('username', ''),
        'email': session.get('email', ''),
        'ssn_last_4': session.get('ssn', '')[-4:] if 'ssn' in session else ''
    }
    return f"Username: {user_info['username']}<br>Email: {user_info['email']}<br>SSN Last 4 Digits: {user_info['ssn_last_4']}"

if __name__ == '__main__':
    app.run(debug=True)