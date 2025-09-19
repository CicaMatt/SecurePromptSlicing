from flask import Flask, session

app = Flask(__name__)
# Set a secret key for sessions to work
app.secret_key = 'your_secret_key_here'

@app.route('/info')
def info():
    # Retrieve information from the session
    username = session.get('username', 'Unknown')
    email = session.get('email', 'Unknown')
    ssn = session.get('ssn', 'Unknown')
    
    return f'Username: {username}, Email: {email}, SSN: {ssn}'

if __name__ == '__main__':
    # Set some example data in the session for testing purposes
    with app.app_context():
        session['username'] = 'JohnDoe'
        session['email'] = 'john.doe@example.com'
        session['ssn'] = '123-45-6789'

    app.run(debug=True)