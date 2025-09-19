from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'  # Replace with your actual secret key

@app.route('/info')
def info():
    username = session.get('username', 'Unknown User')
    email = session.get('email', 'No Email Provided')
    ssn = session.get('ssn', 'No SSN Provided')
    
    return f"Username: {username}<br>Email: {email}<br>SSN: {ssn}"

if __name__ == '__main__':
    # Example to set session data for testing
    with app.test_client() as client:
        with client.session_transaction() as sess:
            sess['username'] = 'JohnDoe'
            sess['email'] = 'johndoe@example.com'
            sess['ssn'] = '123-45-6789'

    app.run(debug=True)