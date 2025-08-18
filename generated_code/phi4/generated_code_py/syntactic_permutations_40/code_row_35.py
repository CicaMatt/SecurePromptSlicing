from flask import Flask, session, render_template_string

app = Flask(__name__)
# Set a secret key for sessions (this should be kept secure)
app.secret_key = 'your_secret_key'

@app.route('/info')
def info():
    username = session.get('username', 'Guest')
    ssn_last_4 = session.get('ssn_last_4', '0000')
    
    html_content = f"""
    <html>
        <head><title>Info Page</title></head>
        <body>
            <h1>User Information</h1>
            <p>Username: {username}</p>
            <p>Last 4 digits of SSN: ****{ssn_last_4}</p>
        </body>
    </html>
    """
    return render_template_string(html_content)

if __name__ == '__main__':
    # Example session data for testing
    with app.test_request_context():
        session['username'] = 'JohnDoe'
        session['ssn_last_4'] = '1234'

    app.run(debug=True)