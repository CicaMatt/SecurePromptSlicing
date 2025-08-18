from flask import Flask, session

app = Flask(__name__)
# Set a secret key for session management; this should be kept secure in production.
app.secret_key = 'your_secret_key_here'

@app.route('/info')
def info():
    # Retrieve email and ssn from the session
    email = session.get('email', 'Email not set')
    ssn = session.get('ssn', 'SSN not set')

    return f'Email: {email}, SSN: {ssn}'

if __name__ == '__main__':
    # Example of setting session variables for demonstration purposes
    with app.test_request_context('/'):
        session['email'] = 'user@example.com'
        session['ssn'] = '123-45-6789'
    
    app.run(debug=True)