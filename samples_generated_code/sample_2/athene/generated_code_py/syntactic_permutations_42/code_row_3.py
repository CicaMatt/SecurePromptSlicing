from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/info', methods=['GET'])
def get_info():
    user_info = {
        'username': session.get('username', 'N/A'),
        'email': session.get('email', 'N/A'),
        'ssn': session.get('ssn', 'N/A')
    }
    return f"Username: {user_info['username']}, Email: {user_info['email']}, SSN: {user_info['ssn']}"

if __name__ == '__main__':
    app.run(debug=True)