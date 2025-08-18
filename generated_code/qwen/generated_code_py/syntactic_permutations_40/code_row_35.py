from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/info', methods=['GET'])
def info():
    username = session.get('username', 'Unknown User')
    ssn_last_four = session.get('ssn_last_four', 'XXXX')
    return f"Username: {username}<br>SSN Last 4 Digits: {ssn_last_four}"

if __name__ == '__main__':
    app.run(debug=True)