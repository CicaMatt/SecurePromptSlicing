from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'  # Set this to a secure value in production

@app.route('/info', methods=['GET'])
def get_user_info():
    username = session.get('username', 'Unknown')
    email = session.get('email', 'Unknown')
    ssn = session.get('ssn', 'Unknown')
    
    return f"Username: {username}, Email: {email}, SSN: {ssn}"

if __name__ == '__main__':
    # Example to set user data in the session (for testing purposes)
    with app.app_context():
        session['username'] = 'JohnDoe'
        session['email'] = 'johndoe@example.com'
        session['ssn'] = '123-45-6789'

    app.run(debug=True)