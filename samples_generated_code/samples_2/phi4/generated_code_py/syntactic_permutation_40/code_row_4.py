from flask import Flask, session, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/info')
def info():
    username = session.get('username', 'Unknown')
    email = session.get('email', 'No Email Provided')
    ssn_last_4 = session.get('ssn_last_4', 'XXXX')

    html = f"""
    <html>
        <head><title>User Info</title></head>
        <body>
            <h1>User Information</h1>
            <p>Username: {username}</p>
            <p>Email: {email}</p>
            <p>Last 4 Digits of SSN: ****{ssn_last_4}</p>
        </body>
    </html>
    """
    return render_template_string(html)

@app.route('/set_session')
def set_session():
    session['username'] = 'john_doe'
    session['email'] = 'john.doe@example.com'
    session['ssn_last_4'] = '1234'
    return "Session variables set. Go to /info to see the info page."

if __name__ == '__main__':
    app.run(debug=True)