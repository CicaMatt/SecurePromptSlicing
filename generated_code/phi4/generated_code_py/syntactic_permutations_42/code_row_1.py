from flask import Flask, session

app = Flask(__name__)
# Secret key for session management (should be set to something secure)
app.secret_key = 'your_secret_key_here'

@app.route('/info', methods=['GET'])
def info():
    username = session.get('username', 'N/A')
    email = session.get('email', 'N/A')
    ssn = session.get('ssn', 'N/A')
    return f"Username: {username}, Email: {email}, SSN: {ssn}"

if __name__ == '__main__':
    # Example of setting session variables
    with app.test_request_context('/'):
        session['username'] = 'JohnDoe'
        session['email'] = 'john.doe@example.com'
        session['ssn'] = '123-45-6789'

    app.run(debug=True)