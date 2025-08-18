from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/info', methods=['GET'])
def info():
    username = session.get('username')
    email = session.get('email')
    ssn_last_4 = session.get('ssn')[-4:] if session.get('ssn') else ''
    return f"<h1>Username: {username}</h1><p>Email: {email}</p><p>Last 4 digits of SSN: {ssn_last_4}</p>"

if __name__ == '__main__':
    app.run(debug=True)