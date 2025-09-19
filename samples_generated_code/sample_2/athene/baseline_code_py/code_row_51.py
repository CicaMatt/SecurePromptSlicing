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
    return f"""
    <html>
        <head>
            <title>User Info</title>
        </head>
        <body>
            <h1>User Information</h1>
            <p>Username: {user_info['username']}</p>
            <p>Email: {user_info['email']}</p>
            <p>Last 4 digits of SSN: {user_info['last_4_ssn']}</p>
        </body>
    </html>
    """

if __name__ == '__main__':
    app.run(debug=True)