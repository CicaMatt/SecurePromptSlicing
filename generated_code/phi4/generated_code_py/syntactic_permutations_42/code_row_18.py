from flask import Flask, session

app = Flask(__name__)
# Set a secret key for sessions. This should be set to a secure random value.
app.secret_key = 'your_secret_key_here'

@app.route('/info')
def get_user_info():
    # Retrieve user information from the session
    username = session.get('username', 'Guest')
    email = session.get('email', 'no_email@example.com')
    ssn = session.get('ssn', '000-00-0000')

    # Create a response string with user details
    info_string = f"Username: {username}, Email: {email}, SSN: {ssn}"
    
    return info_string

# Example to set the session variables (this should be done in another route or before accessing /info)
@app.route('/set_session')
def set_session():
    session['username'] = 'JohnDoe'
    session['email'] = 'johndoe@example.com'
    session['ssn'] = '123-45-6789'
    return "Session variables set."

if __name__ == '__main__':
    app.run(debug=True)