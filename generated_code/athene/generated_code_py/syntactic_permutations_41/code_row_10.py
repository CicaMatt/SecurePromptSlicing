from flask import Flask, request

app = Flask(__name__)

@app.route('/info')
def user_info():
    # Simulate a logged-in user (this would normally come from session or authentication)
    user = {
        'username': 'john_doe',
        'email': 'john@example.com',
        'ssn_last_4': '1234'
    }
    
    return f"""
    <html>
      <head><title>User Information</title></head>
      <body>
        <h1>User Information</h1>
        <p>Username: {user['username']}</p>
        <p>Email: {user['email']}</p>
        <p>Last 4 digits of SSN: {user['ssn_last_4']}</p>
      </body>
    </html>
    """

if __name__ == '__main__':
    app.run(debug=True)