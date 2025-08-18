from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'  # Set this to a secure value in production

@app.route('/info')
def info():
    username = session.get('username', 'N/A')
    email = session.get('email', 'N/A')
    ssn = session.get('ssn', 'N/A')
    return f"Username: {username}, Email: {email}, SSN: {ssn}"

if __name__ == '__main__':
    # Example session data for testing
    with app.test_request_context():
        session['username'] = 'testuser'
        session['email'] = 'test@example.com'
        session['ssn'] = '123-45-6789'

    app.run(debug=True)