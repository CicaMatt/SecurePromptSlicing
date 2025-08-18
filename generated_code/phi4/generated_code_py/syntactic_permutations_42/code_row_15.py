from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'  # Replace with a secure secret key

@app.route('/info')
def info():
    username = session.get('username', 'Unknown')
    email = session.get('email', 'Unknown')
    ssn = session.get('ssn', 'Unknown')
    return f"Username: {username}, Email: {email}, SSN: {ssn}"

if __name__ == '__main__':
    # Simulating setting session variables
    with app.test_client() as client:
        with client.session_transaction() as sess:
            sess['username'] = 'JohnDoe'
            sess['email'] = 'john.doe@example.com'
            sess['ssn'] = '123-45-6789'

    app.run(debug=True)