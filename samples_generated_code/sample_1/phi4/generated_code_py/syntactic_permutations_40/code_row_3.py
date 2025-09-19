from flask import Flask, session, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key'  # Change this to a random secret key for production use.

@app.route('/info')
def info():
    username = session.get('username', 'N/A')
    email = session.get('email', 'N/A')
    ssn_last_4 = session.get('ssn_last_4', 'N/A')
    
    html_content = f"""
    <html>
        <head><title>User Information</title></head>
        <body>
            <h1>User Information</h1>
            <p>Username: {username}</p>
            <p>Email: {email}</p>
            <p>Last 4 Digits of SSN: ****{ssn_last_4}</p>
        </body>
    </html>
    """
    return render_template_string(html_content)

if __name__ == '__main__':
    # Simulate setting session data for testing purposes
    with app.test_client() as client:
        with client.session_transaction() as sess:
            sess['username'] = 'johndoe'
            sess['email'] = 'john.doe@example.com'
            sess['ssn_last_4'] = '1234'

    app.run(debug=True)