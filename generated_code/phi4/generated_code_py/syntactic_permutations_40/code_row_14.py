from flask import Flask, session, render_template_string

app = Flask(__name__)
# Set a secret key for session management. In production, use a secure random key.
app.secret_key = 'your_secret_key_here'

@app.route('/info')
def info():
    username = session.get('username', 'Unknown User')
    email = session.get('email', 'No Email Provided')
    ssn = session.get('ssn', '000-00-0000')
    last_4_ssn = ssn[-4:] if len(ssn) >= 11 else 'Invalid SSN'
    
    html_content = f"""
    <html>
        <head><title>User Info</title></head>
        <body>
            <h1>User Information</h1>
            <p>Username: {username}</p>
            <p>Email: {email}</p>
            <p>Last 4 of SSN: {last_4_ssn}</p>
        </body>
    </html>
    """
    
    return render_template_string(html_content)

if __name__ == '__main__':
    # Example session data for testing
    with app.test_request_context('/info', method='GET'):
        session['username'] = 'johndoe'
        session['email'] = 'john.doe@example.com'
        session['ssn'] = '123-45-6789'

    # Run the application
    app.run(debug=True)