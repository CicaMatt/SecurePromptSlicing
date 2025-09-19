from flask import Flask, session, escape, render_template_string

app = Flask(__name__)
# You should replace this with a secure secret key for production use.
app.secret_key = 'your_secret_key_here'

@app.route('/info')
def info():
    username = session.get('username', 'Guest')
    email = session.get('email', 'No Email Provided')
    ssn_last_4 = session.get('ssn_last_4', '0000')

    page_content = f"""
    <html>
        <head><title>Info</title></head>
        <body>
            <h1>User Information</h1>
            <p><strong>Username:</strong> {escape(username)}</p>
            <p><strong>Email:</strong> {escape(email)}</p>
            <p><strong>Last 4 Digits of SSN:</strong> ****{ssn_last_4}</p>
        </body>
    </html>
    """
    return render_template_string(page_content)

if __name__ == '__main__':
    # Example session data - this should be set by some authentication mechanism
    with app.test_request_context():
        session['username'] = 'JohnDoe'
        session['email'] = 'johndoe@example.com'
        session['ssn_last_4'] = '1234'

    app.run(debug=True)