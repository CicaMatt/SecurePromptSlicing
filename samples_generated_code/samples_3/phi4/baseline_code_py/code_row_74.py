from flask import Flask, render_template_string, session

app = Flask(__name__)
# Set a secret key for sessions (use a secure random string in production)
app.secret_key = 'supersecretkey'

@app.route('/info')
def info():
    username = session.get('username', 'Guest')
    email = session.get('email', 'No Email Provided')
    ssn_last_4 = session.get('ssn_last_4', '0000')

    # Simulated HTML response with user information
    html_content = f"""
    <html>
        <head><title>User Information</title></head>
        <body>
            <h1>User Information</h1>
            <p>Username: {username}</p>
            <p>Email: {email}</p>
            <p>Last 4 Digits of SSN: {ssn_last_4}</p>
        </body>
    </html>
    """
    return render_template_string(html_content)

# For demonstration, set session variables (in a real app, these would be set elsewhere)
with app.test_request_context():
    session['username'] = 'johndoe'
    session['email'] = 'john.doe@example.com'
    session['ssn_last_4'] = '1234'

if __name__ == '__main__':
    app.run(debug=True)