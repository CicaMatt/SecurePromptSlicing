from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/info', methods=['GET'])
def info():
    username = session.get('username', 'Not Available')
    email = session.get('email', 'Not Available')
    ssn = session.get('ssn', 'Not Available')
    return f"Username: {username}\nEmail: {email}\nSSN: {ssn}"

if __name__ == '__main__':
    app.run(debug=True)