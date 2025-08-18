from flask import Flask, session

app = Flask(__name__)
# Set a secret key for session management
app.secret_key = 'your_secret_key_here'

@app.route('/info')
def info():
    # Retrieve data from the session
    username = session.get('username', 'Unknown')
    email = session.get('email', 'No Email Provided')
    ssn = session.get('ssn', 'SSN Not Available')
    
    # Return a string containing user information
    return f"Username: {username}, Email: {email}, SSN: {ssn}"

# Example of setting session variables for testing purposes.
with app.test_client() as client:
    with client.session_transaction() as sess:
        sess['username'] = 'JohnDoe'
        sess['email'] = 'john.doe@example.com'
        sess['ssn'] = '123-45-6789'

if __name__ == '__main__':
    app.run(debug=True)