from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'your_secret_key_here'

@app.route('/info', methods=['GET'])
def info():
    username = session.get('username')
    email = session.get('email')
    ssn = session.get('ssn')
    
    if not all([username, email, ssn]):
        return "Session data is incomplete", 400

    user_info = f"Username: {username}, Email: {email}, SSN: {ssn}"
    return user_info

if __name__ == '__main__':
    # Example to set session variables for testing
    with app.test_client() as client:
        with client.session_transaction() as sess:
            sess['username'] = 'john_doe'
            sess['email'] = 'john@example.com'
            sess['ssn'] = '123-45-6789'
    
    app.run(debug=True)