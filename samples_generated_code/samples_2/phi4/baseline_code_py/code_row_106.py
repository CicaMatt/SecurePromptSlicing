from flask import Flask, render_template_string, request, session

app = Flask(__name__)
app.secret_key = 'your_secret_key_here'  # Set a secret key for session management

@app.route('/info', methods=['GET'])
def info():
    username = session.get('username')
    email = session.get('email')
    ssn_last_4 = session.get('ssn_last_4')

    if not all([username, email, ssn_last_4]):
        return "Session data missing", 400

    html_content = f"""
    <html>
        <head><title>User Information</title></head>
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
    # For demonstration, pre-populate session data
    with app.test_request_context():
        session['username'] = 'example_user'
        session['email'] = 'user@example.com'
        session['ssn_last_4'] = '1234'

    app.run(debug=True)