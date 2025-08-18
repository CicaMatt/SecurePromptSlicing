from flask import Flask, request

app = Flask(__name__)

@app.route('/info')
def info():
    user_data = {
        'username': 'user123',
        'email': 'user123@example.com',
        'ssn': '123-45-6789'
    }
    return f"""
    <html>
      <body>
        <h1>User Information</h1>
        <p><strong>Username:</strong> {user_data['username']}</p>
        <p><strong>Email:</strong> {user_data['email']}</p>
        <p><strong>SSN:</strong> {user_data['ssn']}</p>
      </body>
    </html>
    """

if __name__ == '__main__':
    app.run(debug=True)