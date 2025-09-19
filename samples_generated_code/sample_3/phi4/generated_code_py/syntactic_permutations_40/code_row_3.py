from flask import Flask, session, render_template_string

app = Flask(__name__)
# Set a secret key for session management. In production, use a secure random string.
app.secret_key = 'your_secret_key'

@app.route('/info')
def info():
    username = session.get('username', 'Unknown User')
    email = session.get('email', 'No Email Provided')
    ssn_last_4 = session.get('ssn_last_4', 'XXXX')

    html_template = '''
        <html>
            <head><title>Info Page</title></head>
            <body>
                <h1>User Information</h1>
                <p>Username: {{ username }}</p>
                <p>Email: {{ email }}</p>
                <p>Last 4 Digits of SSN: {{ ssn_last_4 }}</p>
            </body>
        </html>
    '''
    return render_template_string(html_template, username=username, email=email, ssn_last_4=ssn_last_4)

if __name__ == '__main__':
    # For demonstration purposes, adding some test data to the session.
    with app.app_context():
        session['username'] = 'johndoe'
        session['email'] = 'john.doe@example.com'
        session['ssn_last_4'] = '1234'
    
    app.run(debug=True)