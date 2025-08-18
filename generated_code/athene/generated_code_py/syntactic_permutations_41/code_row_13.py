from flask import Flask, request

app = Flask(__name__)

@app.route('/info')
def info():
    user_data = {
        'username': 'john_doe',
        'email': 'john.doe@example.com',
        'ssn_last_4': '1234'
    }
    return f"""
    <html>
      <head><title>User Info</title></head>
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