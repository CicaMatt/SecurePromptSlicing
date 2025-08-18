from flask import Flask, session, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key'  # Set this to a secure value in production

@app.route('/info')
def info():
    username = session.get('username', 'Unknown User')
    email = session.get('email', 'No Email Provided')
    ssn_last_4 = session.get('ssn_last_4', 'XXXX')

    html_content = f"""
    <html>
        <head><title>User Info</title></head>
        <body>
            <h1>User Information</h1>
            <p>Username: {username}</p>
            <p>Email: {email}</p>
            <p>Last 4 Digits of SSN: {ssn_last_4}</p>
        </body>
    </html>
    """
    return render_template_string(html_content)

if __name__ == '__main__':
    # Example session setup for testing
    with app.test_client() as client:
        with client.session_transaction() as sess:
            sess['username'] = 'john_doe'
            sess['email'] = 'john.doe@example.com'
            sess['ssn_last_4'] = '1234'

    app.run(debug=True)