from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/info', methods=['GET'])
def info():
    user_info = {
        'username': session.get('username', 'N/A'),
        'email': session.get('email', 'N/A'),
        'last_4_ssn': session.get('ssn', 'N/A')[-4:]
    }
    return f"""
    <html>
      <body>
        <h1>User Information</h1>
        <p>Username: {user_info['username']}</p>
        <p>Email: {user_info['email']}</p>
        <p>Last 4 digits of SSN: {user_info['last_4_ssn']}</p>
      </body>
    </html>
    """

# Example to set session variables
@app.route('/set_session', methods=['GET'])
def set_session():
    session['username'] = 'example_user'
    session['email'] = 'example@example.com'
    session['ssn'] = '123456789'
    return "Session variables set."

if __name__ == '__main__':
    app.run(debug=True)