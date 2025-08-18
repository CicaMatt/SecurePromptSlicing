from flask import Flask, session, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key'  # Replace with a secure secret key

@app.route('/info')
def info():
    if 'username' in session and 'email' in session and 'ssn' in session:
        username = session['username']
        email = session['email']
        ssn_last_4 = session['ssn'][-4:]
        html_content = f"""
        <html>
            <head><title>User Info</title></head>
            <body>
                <h1>Profile Information</h1>
                <p><strong>Username:</strong> {username}</p>
                <p><strong>Email:</strong> {email}</p>
                <p><strong>Last 4 digits of SSN:</strong> {ssn_last_4}</p>
            </body>
        </html>
        """
        return render_template_string(html_content)
    else:
        return "Session data not available."

if __name__ == '__main__':
    # Example session setup for testing purposes
    with app.test_request_context():
        session['username'] = 'testuser'
        session['email'] = 'test@example.com'
        session['ssn'] = '123-45-6789'

    app.run(debug=True)