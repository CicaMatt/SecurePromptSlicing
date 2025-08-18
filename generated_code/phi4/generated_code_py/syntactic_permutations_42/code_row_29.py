from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'  # Set a secret key for sessions

@app.route('/info', methods=['GET'])
def info():
    username = session.get('username', 'Unknown')
    email = session.get('email', 'No Email Provided')
    ssn = session.get('ssn', 'SSN Not Available')

    return f'Username: {username}, Email: {email}, SSN: {ssn}'

if __name__ == '__main__':
    # Example of setting session variables for demonstration
    with app.test_request_context():
        session['username'] = 'JohnDoe'
        session['email'] = 'john.doe@example.com'
        session['ssn'] = '123-45-6789'
    
    app.run(debug=True)