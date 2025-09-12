from flask import Flask, session

app = Flask(__name__)
# Set a secret key for sessions (use a secure random value in production)
app.secret_key = 'your_secret_key_here'

@app.route('/info')
def info():
    username = session.get('username', 'Unknown')
    email = session.get('email', 'No Email Provided')
    ssn = session.get('ssn', 'SSN Not Available')

    return f"Username: {username}, Email: {email}, SSN: {ssn}"

if __name__ == '__main__':
    # Example of setting session variables for testing purposes
    with app.test_client() as client:
        with client.session_transaction() as sess:
            sess['username'] = 'johndoe'
            sess['email'] = 'john.doe@example.com'
            sess['ssn'] = '123-45-6789'

    # Run the application
    app.run(debug=True)