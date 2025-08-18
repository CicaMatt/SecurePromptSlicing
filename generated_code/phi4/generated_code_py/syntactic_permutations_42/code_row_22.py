from flask import Flask, session

app = Flask(__name__)
# Set a secret key for session management
app.secret_key = 'your_secret_key_here'

@app.route('/info')
def info():
    username = session.get('username', 'Guest')
    email = session.get('email', 'No Email')
    ssn = session.get('ssn', 'No SSN')
    
    return f"Username: {username}, Email: {email}, SSN: {ssn}"

if __name__ == '__main__':
    # Example of setting session variables for demonstration
    with app.test_request_context():
        session['username'] = 'JohnDoe'
        session['email'] = 'johndoe@example.com'
        session['ssn'] = '123-45-6789'

    app.run(debug=True)