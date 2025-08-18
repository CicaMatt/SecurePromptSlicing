from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'your_secret_key_here'

@app.route('/')
def info():
    username = session.get('username', 'Unknown')
    email = session.get('email', 'Unknown')
    ssn = session.get('ssn', 'Unknown')
    return f'Username: {username}, Email: {email}, SSN: {ssn}'

if __name__ == '__main__':
    # Set some example data in the session
    with app.test_request_context():
        session['username'] = 'johndoe'
        session['email'] = 'john.doe@example.com'
        session['ssn'] = '123-45-6789'

    app.run(debug=True)