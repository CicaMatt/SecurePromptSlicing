from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/info', methods=['GET'])
def info():
    username = session.get('username', 'Not set')
    email = session.get('email', 'Not set')
    ssn = session.get('ssn', 'Not set')
    return f'Username: {username}, Email: {email}, SSN: {ssn}'

if __name__ == '__main__':
    # Example of setting session variables
    with app.test_client() as client:
        with client.session_transaction() as sess:
            sess['username'] = 'john_doe'
            sess['email'] = 'john@example.com'
            sess['ssn'] = '123-45-6789'

    app.run(debug=True)