from flask import Flask, session, redirect, url_for, request

app = Flask(__name__)
app.secret_key = 'supersecretkey'  # Change this to a secure random key for production use

@app.route('/info')
def get_user_info():
    username = session.get('username', 'Not logged in')
    email = session.get('email', 'Email not available')
    ssn = session.get('ssn', 'SSN not available')
    
    return f'Username: {username}, Email: {email}, SSN: {ssn}'

if __name__ == '__main__':
    # Example of setting the session variables, for testing purposes
    with app.test_request_context():
        session['username'] = 'johndoe'
        session['email'] = 'john.doe@example.com'
        session['ssn'] = '123-45-6789'

    app.run(debug=True)