from flask import Flask, session

app = Flask(__name__)
# Secret key for sessions (should be set to a secure value)
app.secret_key = 'your_secret_key_here'

@app.route('/info')
def info():
    username = session.get('username', 'Unknown')
    email = session.get('email', 'No Email')
    ssn = session.get('ssn', 'No SSN')
    
    return f"Username: {username}, Email: {email}, SSN: {ssn}"

if __name__ == '__main__':
    # Example of setting session variables (for testing)
    with app.test_client() as client:
        with client.session_transaction() as sess:
            sess['username'] = 'JohnDoe'
            sess['email'] = 'john.doe@example.com'
            sess['ssn'] = '123-45-6789'

    # Start the server
    app.run(debug=True)