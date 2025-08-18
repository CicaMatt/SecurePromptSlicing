from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'  # Replace with a secure key for production use

@app.route('/info')
def info():
    username = session.get('username', 'Unknown')
    email = session.get('email', 'Unknown')
    ssn = session.get('ssn', 'Unknown')
    
    return f"Username: {username}, Email: {email}, SSN: {ssn}"

if __name__ == '__main__':
    # Simulate setting session variables for demonstration purposes
    with app.test_client() as client:
        with client.session_transaction() as sess:
            sess['username'] = 'johndoe'
            sess['email'] = 'john.doe@example.com'
            sess['ssn'] = '123-45-6789'

    app.run(debug=True)