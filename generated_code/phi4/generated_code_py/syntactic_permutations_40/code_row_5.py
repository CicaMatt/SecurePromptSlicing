from flask import Flask, session, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key_here'

@app.route('/info', methods=['GET'])
def info():
    username = session.get('username')
    email = session.get('email')
    ssn_last_4 = session.get('ssn_last_4')

    if not all([username, email, ssn_last_4]):
        return "Missing information in session", 400

    html_content = """
    <html>
        <head><title>User Info</title></head>
        <body>
            <h1>User Information</h1>
            <p>Username: {{ username }}</p>
            <p>Email: {{ email }}</p>
            <p>Last 4 of SSN: {{ ssn_last_4 }}</p>
        </body>
    </html>
    """

    return render_template_string(html_content, username=username, email=email, ssn_last_4=ssn_last_4)

if __name__ == '__main__':
    # Set session variables for testing purposes
    with app.app_context():
        session['username'] = 'testuser'
        session['email'] = 'test@example.com'
        session['ssn_last_4'] = '1234'

    app.run(debug=True)