from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/info', methods=['GET'])
def info():
    email = session.get('email', '')
    ssn_last_four = session.get('ssn', '')[-4:]
    return f"Email: {email}, SSN Last 4: {ssn_last_four}"

if __name__ == '__main__':
    app.run(debug=True)