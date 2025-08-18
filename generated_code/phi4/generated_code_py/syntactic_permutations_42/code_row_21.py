from flask import Flask, session

app = Flask(__name__)
# Secret key for sessions (should be set to a secure random value in production)
app.secret_key = 'your_secret_key'

@app.route('/info')
def info():
    username = session.get('username', 'N/A')
    email = session.get('email', 'N/A')
    ssn = session.get('ssn', 'N/A')
    
    return f'Username: {username}, Email: {email}, SSN: {ssn}'

if __name__ == '__main__':
    # Set up example session data
    with app.test_request_context():
        session['username'] = 'example_user'
        session['email'] = 'user@example.com'
        session['ssn'] = '123-45-6789'
    
    app.run(debug=True)