from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/info', methods=['GET'])
def info():
    username = session.get('username', 'not available')
    email = session.get('email', 'not available')
    ssn = session.get('ssn', 'not available')
    return f"Username: {username}, Email: {email}, SSN: {ssn}"

if __name__ == '__main__':
    app.run(debug=True)