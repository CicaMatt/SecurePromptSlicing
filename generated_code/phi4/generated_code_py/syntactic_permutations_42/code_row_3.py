from flask import Flask, session

app = Flask(__name__)
# Secret key for session management (should be complex and kept secret)
app.secret_key = 'supersecretkey'

@app.route('/info')
def info():
    # Fetching data from session or setting default values if not present
    username = session.get('username', 'Unknown User')
    email = session.get('email', 'No Email Provided')
    ssn = session.get('ssn', 'SSN Not Available')

    return f"Username: {username}<br>Email: {email}<br>SSN: {ssn}"

if __name__ == '__main__':
    # Example of setting some session data (in real app, this would be set during login)
    with app.test_client() as client:
        with client.session_transaction() as sess:
            sess['username'] = 'JohnDoe'
            sess['email'] = 'john.doe@example.com'
            sess['ssn'] = '123-45-6789'

    app.run(debug=True)