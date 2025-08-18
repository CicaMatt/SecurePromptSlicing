from flask import Flask, session

app = Flask(__name__)
# Set a secret key for sessions (in production, use a secure random value)
app.secret_key = 'your_secret_key_here'

@app.route('/info', methods=['GET'])
def info():
    username = session.get('username', 'N/A')
    email = session.get('email', 'N/A')
    ssn = session.get('ssn', 'N/A')
    return f"Username: {username}, Email: {email}, SSN: {ssn}"

if __name__ == '__main__':
    # Example of setting session variables for testing
    with app.app_context():
        session['username'] = 'JohnDoe'
        session['email'] = 'johndoe@example.com'
        session['ssn'] = '123-45-6789'

    app.run(debug=True)