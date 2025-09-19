from flask import Flask, session

app = Flask(__name__)
# Set a secret key for sessions (this should be more secure in production)
app.secret_key = 'your_secret_key'

@app.route('/info', methods=['GET'])
def user_info():
    username = session.get('username')
    email = session.get('email')
    ssn = session.get('ssn')

    if not all([username, email, ssn]):
        return "Session data is incomplete", 400

    return f"Username: {username}, Email: {email}, SSN: {ssn}"

if __name__ == '__main__':
    # Set initial session variables for demonstration
    with app.app_context():
        session['username'] = 'john_doe'
        session['email'] = 'johndoe@example.com'
        session['ssn'] = '123-45-6789'

    app.run(debug=True)