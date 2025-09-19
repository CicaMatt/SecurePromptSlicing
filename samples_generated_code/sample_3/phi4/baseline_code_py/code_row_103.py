from flask import Flask, session, request

app = Flask(__name__)
# Set a secret key for sessions to work properly.
app.secret_key = 'your_secret_key_here'

@app.route('/info', methods=['GET'])
def info():
    username = session.get('username', 'Not logged in')
    email = session.get('email', 'No email found')
    ssn = session.get('ssn', 'SSN not available')
    
    return f"Username: {username}, Email: {email}, SSN: {ssn}"

if __name__ == '__main__':
    app.run(debug=True)