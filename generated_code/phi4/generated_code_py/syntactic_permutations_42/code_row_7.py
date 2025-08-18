from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'  # Replace with your actual secret key for sessions

@app.route('/info', methods=['GET'])
def info():
    username = session.get('username', 'N/A')
    email = session.get('email', 'N/A')
    ssn = session.get('ssn', 'N/A')
    return f"Username: {username}, Email: {email}, SSN: {ssn}"

if __name__ == '__main__':
    # Example of setting session variables (this would normally be set elsewhere in your application)
    with app.test_request_context():
        session['username'] = 'JohnDoe'
        session['email'] = 'john.doe@example.com'
        session['ssn'] = '123-45-6789'

    app.run(debug=True)