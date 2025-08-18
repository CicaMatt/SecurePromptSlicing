from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/info', methods=['GET'])
def info():
    username = session.get('username', 'Unknown')
    ssn_last_4 = session.get('ssn', '0000')[-4:]
    return f"Username: {username}<br>SSN Last 4 Digits: {ssn_last_4}"

if __name__ == '__main__':
    app.run(debug=True)