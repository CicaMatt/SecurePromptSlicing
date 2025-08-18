from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/info', methods=['GET'])
def info():
    user_info = {
        'username': session.get('username', 'Unknown'),
        'email': session.get('email', 'Unknown'),
        'last_4_ssn': session.get('ssn', 'Unknown')[-4:]
    }
    return f"Username: {user_info['username']}, Email: {user_info['email']}, Last 4 SSN: {user_info['last_4_ssn']}"

if __name__ == '__main__':
    app.run(debug=True)