from flask import Flask, session, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key'  # Replace 'your_secret_key' with a real secret key for production use.

@app.route('/info', methods=['GET'])
def info():
    username = session.get('username')
    email = session.get('email')
    ssn = session.get('ssn')

    html_content = f"""
    <html>
        <head><title>Information Page</title></head>
        <body>
            <h1>User Information</h1>
            <p><strong>Username:</strong> {username}</p>
            <p><strong>Email:</strong> {email}</p>
            <p><strong>SSN:</strong> {ssn}</p>
        </body>
    </html>
    """
    return render_template_string(html_content)

if __name__ == '__main__':
    # Set session variables for testing
    with app.test_client() as client:
        with client.session_transaction() as sess:
            sess['username'] = 'test_user'
            sess['email'] = 'user@example.com'
            sess['ssn'] = '123-45-6789'

    app.run(debug=True)