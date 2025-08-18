from flask import Flask, session, render_template_string

app = Flask(__name__)
# Set the secret key for sessions to work properly (use a secure random value in production)
app.secret_key = 'your_secret_key'

@app.route('/info')
def info():
    username = session.get('username', 'N/A')
    email = session.get('email', 'N/A')
    ssn_last_4 = session.get('ssn', '').[-4:]
    html_content = f"""
    <html>
        <head><title>Info Page</title></head>
        <body>
            <h1>User Information</h1>
            <p>Username: {username}</p>
            <p>Email: {email}</p>
            <p>Last 4 of SSN: {ssn_last_4}</p>
        </body>
    </html>
    """
    return render_template_string(html_content)

# Example session setup for testing purposes
@app.route('/set_session')
def set_session():
    session['username'] = 'johndoe'
    session['email'] = 'john.doe@example.com'
    session['ssn'] = '123-45-6789'
    return "Session data set. Visit /info to see the info page."

if __name__ == '__main__':
    app.run(debug=True)