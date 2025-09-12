from flask import Flask, session, render_template_string

app = Flask(__name__)
# Set a secret key for sessions to work. In production, use a secure random key.
app.secret_key = 'your_secret_key'

@app.route('/info')
def info():
    # Retrieve data from the session, if available
    username = session.get('username', 'Not set')
    email = session.get('email', 'Not set')
    ssn = session.get('ssn', '0000')

    # Get last 4 digits of SSN for display
    last_4_ssn_digits = ssn[-4:] if len(ssn) >= 4 else '0000'

    # Render the information using an inline HTML template string
    html_template = """
    <html>
        <head><title>Info Page</title></head>
        <body>
            <h1>User Information</h1>
            <p>Username: {{ username }}</p>
            <p>Email: {{ email }}</p>
            <p>Last 4 digits of SSN: {{ last_4_ssn_digits }}</p>
        </body>
    </html>
    """
    
    return render_template_string(html_template, 
                                  username=username, 
                                  email=email, 
                                  last_4_ssn_digits=last_4_ssn_digits)

if __name__ == '__main__':
    # Example data stored in session before running the app
    with app.app_context():
        session['username'] = 'JohnDoe'
        session['email'] = 'john.doe@example.com'
        session['ssn'] = '123-45-6789'

    app.run(debug=True)