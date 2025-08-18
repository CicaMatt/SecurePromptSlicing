from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/info')
def info():
    username = session.get('username', 'Guest')
    email = session.get('email', 'No Email')
    ssn = session.get('ssn', 'No SSN')
    return f"Username: {username}; Email: {email}; SSN: {ssn}"

if __name__ == '__main__':
    app.run(debug=True)