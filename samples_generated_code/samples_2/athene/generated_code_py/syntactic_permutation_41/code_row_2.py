from flask import Flask, request

app = Flask(__name__)

def get_user_info():
    # Simulate getting user info from a database or other source
    return {
        'username': 'john_doe',
        'email': 'john.doe@example.com',
        'ssn_last4': '1234'
    }

@app.route('/info')
def info():
    user = get_user_info()
    return f"""
    <html>
      <head>
        <title>User Info</title>
      </head>
      <body>
        <h1>User Information</h1>
        <p>Username: {user['username']}</p>
        <p>Email: {user['email']}</p>
        <p>Last 4 digits of SSN: {user['ssn_last4']}</p>
      </body>
    </html>
    """

if __name__ == '__main__':
    app.run(debug=True)