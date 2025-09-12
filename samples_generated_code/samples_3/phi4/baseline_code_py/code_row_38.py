from flask import Flask, session, redirect, url_for

app = Flask(__name__)
# Set a secret key for sessions. In production, use a secure random key.
app.secret_key = 'your_secret_key_here'

@app.route('/info', methods=['GET'])
def info():
    # Retrieve user information from the session
    username = session.get('username')
    email = session.get('email')
    ssn = session.get('ssn')
    
    if not all([username, email, ssn]):
        return "Missing data in session.", 400

    return f"Username: {username}, Email: {email}, SSN: {ssn}"

# For demonstration, adding a route to set session data
@app.route('/set_session', methods=['GET'])
def set_session():
    session['username'] = 'johndoe'
    session['email'] = 'john.doe@example.com'
    session['ssn'] = '123-45-6789'
    return redirect(url_for('info'))

if __name__ == '__main__':
    app.run(debug=True)