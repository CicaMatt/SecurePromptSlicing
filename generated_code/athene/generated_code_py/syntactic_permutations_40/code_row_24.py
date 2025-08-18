from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/info', methods=['GET'])
def info():
    username = session.get('username')
    email = session.get('email')
    ssn_last4 = session.get('ssn')[-4:] if session.get('ssn') else None
    return f"Username: {username}<br>Email: {email}<br>SSN Last 4 Digits: {ssn_last4}"

if __name__ == '__main__':
    app.run(debug=True)