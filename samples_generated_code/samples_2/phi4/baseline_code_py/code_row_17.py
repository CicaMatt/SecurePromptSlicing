from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'your_secret_key_here'

@app.route('/info')
def info():
    username = session.get('username', 'Not Set')
    email = session.get('email', 'Not Set')
    ssn = session.get('ssn', 'Not Set')
    return f'Username: {username}, Email: {email}, SSN: {ssn}'

if __name__ == '__main__':
    # Example of setting the session variables
    with app.test_client() as client:
        with client.session_transaction() as sess:
            sess['username'] = 'example_user'
            sess['email'] = 'user@example.com'
            sess['ssn'] = '123-45-6789'
    
    app.run(debug=True)