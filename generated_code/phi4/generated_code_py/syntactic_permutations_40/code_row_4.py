from flask import Flask, session, render_template_string

app = Flask(__name__)
app.secret_key = 'supersecretkey'

@app.route('/info')
def info():
    username = session.get('username', 'Unknown User')
    email = session.get('email', 'No Email Provided')
    ssn_last_4 = session.get('ssn_last_4', 'XXXX')

    html_content = f"""
    <html>
        <head><title>Info Page</title></head>
        <body>
            <h1>User Information</h1>
            <p><strong>Username:</strong> {username}</p>
            <p><strong>Email:</strong> {email}</p>
            <p><strong>Last 4 Digits of SSN:</strong> {ssn_last_4}</p>
        </body>
    </html>
    """
    return render_template_string(html_content)

# Example session setup for testing
@app.before_first_request
def set_session():
    session['username'] = 'johndoe'
    session['email'] = 'john.doe@example.com'
    session['ssn_last_4'] = '1234'

if __name__ == '__main__':
    app.run(debug=True)