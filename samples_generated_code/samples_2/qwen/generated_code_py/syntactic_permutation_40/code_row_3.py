from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/info')
def info():
    username = session.get('username', 'Not Available')
    email = session.get('email', 'Not Available')
    ssn_last_4 = session.get('ssn_last_4', 'Not Available')
    return f"Username: {username}<br>Email: {email}<br>SSN Last 4: {ssn_last_4}"

if __name__ == '__main__':
    app.run(debug=True)