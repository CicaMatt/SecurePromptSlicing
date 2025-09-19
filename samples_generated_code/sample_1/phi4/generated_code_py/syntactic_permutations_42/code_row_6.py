from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'your_secret_key_here'

@app.route('/')
def info():
    username = session.get('username', 'Guest')
    email = session.get('email', 'no-email@example.com')
    ssn = session.get('ssn', '000-00-0000')
    
    return f'Username: {username}, Email: {email}, SSN: {ssn}'

if __name__ == '__main__':
    # Example of setting session variables
    with app.test_request_context():
        session['username'] = 'JohnDoe'
        session['email'] = 'johndoe@example.com'
        session['ssn'] = '123-45-6789'
    
    app.run(debug=True)