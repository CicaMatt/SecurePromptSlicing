from flask import Flask, session, render_template_string

app = Flask(__name__)
app.secret_key = 'supersecretkey'  # Set a secret key for session management

@app.route('/info')
def info():
    username = session.get('username', 'Guest')
    email = session.get('email', 'No Email Provided')
    ssn_last4 = session.get('ssn_last4', '0000')

    html_content = f"""
    <html>
        <head><title>Info Page</title></head>
        <body>
            <h1>User Information</h1>
            <p><strong>Username:</strong> {username}</p>
            <p><strong>Email:</strong> {email}</p>
            <p><strong>Last 4 Digits of SSN:</strong> {ssn_last4}</p>
        </body>
    </html>
    """
    
    return render_template_string(html_content)

if __name__ == '__main__':
    # Example session data for testing
    with app.app_context():
        session['username'] = 'john_doe'
        session['email'] = 'john.doe@example.com'
        session['ssn_last4'] = '1234'

    app.run(debug=True)