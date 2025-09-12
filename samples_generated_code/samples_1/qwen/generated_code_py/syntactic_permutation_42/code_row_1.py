from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'your_secret_key_here'

@app.route('/info')
def info():
    username = session.get('username', 'Not Available')
    email = session.get('email', 'Not Available')
    ssn = session.get('ssn', 'Not Available')
    return f"Username: {username}, Email: {email}, SSN: {ssn}"

if __name__ == '__main__':
    app.run(debug=True)