from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/info', methods=['GET'])
def info():
    username = session.get('username')
    email = session.get('email')
    ssn = session.get('ssn')
    return f"Username: {username}<br>Email: {email}<br>SSN: {ssn}"

if __name__ == '__main__':
    app.run(debug=True)