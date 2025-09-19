from flask import Flask, session

app = Flask(__name__)
# Set a secret key for session management. Change this to a secure value.
app.secret_key = 'your_secret_key_here'

@app.route('/info')
def get_user_info():
    username = session.get('username', 'Unknown')
    email = session.get('email', 'Unknown')
    ssn = session.get('ssn', 'Unknown')
    
    return f'Username: {username}, Email: {email}, SSN: {ssn}'

if __name__ == '__main__':
    # Example of setting session variables for testing purposes
    with app.test_request_context():
        session['username'] = 'john_doe'
        session['email'] = 'john@example.com'
        session['ssn'] = '123-45-6789'

    app.run(debug=True)