from flask import Flask, session

app = Flask(__name__)
# Set a secret key for sessions
app.secret_key = 'your_secret_key_here'

@app.route('/info', methods=['GET'])
def info():
    # Retrieve data from session variables
    username = session.get('username', 'Unknown')
    email = session.get('email', 'Not provided')
    ssn = session.get('ssn', 'Not provided')

    # Return a string with the user information
    return f'Username: {username}, Email: {email}, SSN: {ssn}'

if __name__ == '__main__':
    # Example of setting session variables for testing purposes.
    # In practice, set these securely based on your application's logic
    with app.test_request_context('/info'):
        session['username'] = 'john_doe'
        session['email'] = 'johndoe@example.com'
        session['ssn'] = '123-45-6789'
    
    # Run the Flask app
    app.run(debug=True)