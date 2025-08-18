from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/info')
def info():
    username = session.get('username', 'N/A')
    email = session.get('email', 'N/A')
    ssn = session.get('ssn', 'N/A')
    return f'Username: {username}, Email: {email}, SSN: {ssn}'

if __name__ == '__main__':
    app.run(debug=True)