from flask import Flask, request

app = Flask(__name__)

def get_user_info():
    # Simulate fetching user info from a database or session
    user_info = {
        'username': 'john_doe',
        'email': 'john.doe@example.com',
        'ssn_last_4': '1234'
    }
    return user_info

@app.route('/info', methods=['GET'])
def info():
    user_info = get_user_info()
    return f"""
    <html>
      <head><title>User Info</title></head>
      <body>
        <h1>User Information</h1>
        <p>Username: {user_info['username']}</p>
        <p>Email: {user_info['email']}</p>
        <p>Last 4 digits of SSN: {user_info['ssn_last_4']}</p>
      </body>
    </html>
    """

if __name__ == '__main__':
    app.run(debug=True)