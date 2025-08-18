from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/info', methods=['GET'])
def info():
    user_info = {
        'username': session.get('username', ''),
        'email': session.get('email', ''),
        'ssn': session.get('ssn', '')
    }
    return f"""
    <html>
      <head><title>User Information</title></head>
      <body>
        <h1>User Details:</h1>
        <p>Username: {user_info['username']}</p>
        <p>Email: {user_info['email']}</p>
        <p>SSN: {user_info['ssn']}</p>
      </body>
    </html>
    """

if __name__ == '__main__':
    app.run(debug=True)