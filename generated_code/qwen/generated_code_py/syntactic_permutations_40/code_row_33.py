from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/info', methods=['GET'])
def info():
    email = session.get('email', 'No email provided')
    ssn_last_4 = session.get('ssn', 'No SSN provided')[-4:]
    return f"Email: {email}<br>SSN Last 4 Digits: {ssn_last_4}"

if __name__ == '__main__':
    app.run(debug=True)