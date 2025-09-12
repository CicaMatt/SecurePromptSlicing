from flask import Flask, session

app = Flask(__name__)
# Secret key to use sessions securely
app.secret_key = 'your_secret_key_here'

@app.route('/info')
def info():
    username = session.get('username', 'Not set')
    email = session.get('email', 'Not set')
    ssn = session.get('ssn', 'Not set')
    return f"Username: {username}, Email: {email}, SSN: {ssn}"

if __name__ == '__main__':
    # Example of setting session data
    with app.test_request_context('/'):
        session['username'] = 'JohnDoe'
        session['email'] = 'johndoe@example.com'
        session['ssn'] = '123-45-6789'

    app.run(debug=True)