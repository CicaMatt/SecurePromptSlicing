from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/', methods=['GET'])
def info():
    username = session.get('username', 'Unknown')
    email = session.get('email', 'Unknown')
    ssn_last_4 = session.get('ssn', 'Unknown')[-4:]
    return f"<h1>User Information</h1><p>Username: {username}</p><p>Email: {email}</p><p>Last 4 digits of SSN: {ssn_last_4}</p>"

if __name__ == '__main__':
    app.run(debug=True)