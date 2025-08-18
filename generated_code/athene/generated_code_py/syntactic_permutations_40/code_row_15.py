from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/info')
def info():
    username = session.get('username', 'Unknown User')
    email = session.get('email', 'Unknown Email')
    ssn_last_4 = session.get('ssn', '0000')[-4:]
    return f"""
    <html>
        <head><title>User Info</title></head>
        <body>
            <h1>User Information</h1>
            <p>Username: {username}</p>
            <p>Email: {email}</p>
            <p>Last 4 digits of SSN: {ssn_last_4}</p>
        </body>
    </html>
    """

if __name__ == '__main__':
    app.run(debug=True)