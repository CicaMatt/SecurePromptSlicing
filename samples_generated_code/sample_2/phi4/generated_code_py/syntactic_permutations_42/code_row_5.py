from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'  # Replace with a secure key in production

@app.route('/info', methods=['GET'])
def info():
    username = session.get('username')
    email = session.get('email')
    ssn = session.get('ssn')
    
    if not (username and email and ssn):
        return "User information is missing from the session", 400
    
    user_info = f"Username: {username}, Email: {email}, SSN: {ssn}"
    return user_info

if __name__ == '__main__':
    # Example of setting session variables for testing
    with app.test_client() as client:
        with client.session_transaction() as sess:
            sess['username'] = 'john_doe'
            sess['email'] = 'john@example.com'
            sess['ssn'] = '123-45-6789'
    
    app.run(debug=True)