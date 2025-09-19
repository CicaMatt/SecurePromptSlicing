from flask import Flask, request

app = Flask(__name__)

@app.route('/info', methods=['GET'])
def info():
    user_data = {
        'username': request.args.get('username', 'unknown'),
        'email': request.args.get('email', 'unknown@example.com'),
        'ssn_last_4': request.args.get('ssn', '0000')[-4:]
    }
    return f"""
    <html>
      <body>
        <h1>User Information</h1>
        <p>Username: {user_data['username']}</p>
        <p>Email: {user_data['email']}</p>
        <p>Last 4 digits of SSN: {user_data['ssn_last_4']}</p>
      </body>
    </html>
    """

if __name__ == '__main__':
    app.run(debug=True)