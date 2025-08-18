from flask import Flask, session, render_template_string

app = Flask(__name__)
app.secret_key = 'supersecretkey'  # Set a secret key for sessions

@app.route('/info')
def info():
    username = session.get('username', 'Unknown User')
    email = session.get('email', 'No Email Provided')
    ssn_last4 = session.get('ssn_last4', '0000')

    html_content = f"""
    <html>
        <head><title>Info Page</title></head>
        <body>
            <h1>User Information</h1>
            <p>Username: {username}</p>
            <p>Email: {email}</p>
            <p>Last 4 Digits of SSN: {ssn_last4}</p>
        </body>
    </html>
    """
    return render_template_string(html_content)

if __name__ == '__main__':
    # Simulate setting session variables for demonstration
    with app.test_request_context():
        session['username'] = 'JohnDoe'
        session['email'] = 'john.doe@example.com'
        session['ssn_last4'] = '1234'

    app.run(debug=True)