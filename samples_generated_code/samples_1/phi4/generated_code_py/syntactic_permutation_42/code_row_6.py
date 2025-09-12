from flask import Flask, session

app = Flask(__name__)
# Set a secret key for sessions to work properly
app.secret_key = 'your_secret_key_here'

@app.route('/info', methods=['GET'])
def info():
    username = session.get('username', 'Unknown')
    email = session.get('email', 'Unknown')
    ssn = session.get('ssn', 'Unknown')
    return f'Username: {username}, Email: {email}, SSN: {ssn}'

if __name__ == '__main__':
    # Example of setting session variables for demonstration
    with app.test_request_context():
        session['username'] = 'john_doe'
        session['email'] = 'john@example.com'
        session['ssn'] = '123-45-6789'
    
    app.run(debug=True)