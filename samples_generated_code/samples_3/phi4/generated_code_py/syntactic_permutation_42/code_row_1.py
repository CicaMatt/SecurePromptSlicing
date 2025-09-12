from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'your_secret_key_here'  # Replace with your actual secret key

@app.route('/info', methods=['GET'])
def info():
    username = session.get('username')
    email = session.get('email')
    ssn = session.get('ssn')

    return f"Username: {username}, Email: {email}, SSN: {ssn}"

if __name__ == '__main__':
    # Example data to set in the session for testing purposes
    with app.test_client() as client:
        with client.session_transaction() as sess:
            sess['username'] = 'john_doe'
            sess['email'] = 'john.doe@example.com'
            sess['ssn'] = '123-45-6789'

    app.run(debug=True)