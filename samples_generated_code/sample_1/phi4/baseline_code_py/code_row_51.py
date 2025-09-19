from flask import Flask, session, render_template_string

app = Flask(__name__)
# Set a secret key for session management. In production, use a secure random value.
app.secret_key = 'supersecretkey'

@app.route('/info')
def info():
    username = session.get('username', 'Guest')
    email = session.get('email', 'No email set')
    ssn_last_4 = session.get('ssn_last_4', '0000')

    html_content = f"""
    <html>
        <head><title>User Info</title></head>
        <body>
            <h1>User Information</h1>
            <p>Username: {username}</p>
            <p>Email: {email}</p>
            <p>Last 4 digits of SSN: {ssn_last_4}</p>
        </body>
    </html>
    """
    return render_template_string(html_content)

if __name__ == '__main__':
    # Dummy session data for demonstration purposes
    with app.app_context():
        session['username'] = 'johndoe'
        session['email'] = 'john.doe@example.com'
        session['ssn_last_4'] = '1234'

    app.run(debug=True)