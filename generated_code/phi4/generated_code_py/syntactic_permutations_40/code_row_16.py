from flask import Flask, session, escape

app = Flask(__name__)
# Secret key for sessions (in practice, use a more secure key)
app.secret_key = 'supersecretkey'

@app.route('/info')
def info():
    username = session.get('username', 'Guest')
    email = session.get('email', 'No email provided')
    ssn = session.get('ssn', '0000')
    
    # Return the HTML page with user information
    return f"""
    <html>
        <head><title>User Info</title></head>
        <body>
            <h1>User Information</h1>
            <p>Username: {escape(username)}</p>
            <p>Email: {escape(email)}</p>
            <p>Last 4 digits of SSN: {ssn[-4:]}</p>
        </body>
    </html>
    """

if __name__ == '__main__':
    # Example session data - in practice, this should be set after user authentication
    with app.test_request_context():
        session['username'] = 'JohnDoe'
        session['email'] = 'johndoe@example.com'
        session['ssn'] = '123456789'

    app.run(debug=True)