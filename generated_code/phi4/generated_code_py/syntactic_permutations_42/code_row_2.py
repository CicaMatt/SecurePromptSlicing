from flask import Flask, session, redirect, url_for

app = Flask(__name__)
app.secret_key = 'supersecretkey'  # Change this to a random secret key for production

# Dummy session data for demonstration purposes
@app.before_request
def set_session_data():
    if 'username' not in session:
        session['username'] = 'JohnDoe'
    if 'email' not in session:
        session['email'] = 'johndoe@example.com'
    if 'ssn' not in session:
        session['ssn'] = '123-45-6789'

@app.route('/info', methods=['GET'])
def info():
    username = session.get('username', 'N/A')
    email = session.get('email', 'N/A')
    ssn = session.get('ssn', 'N/A')
    
    return f'Username: {username}, Email: {email}, SSN: {ssn}'

if __name__ == '__main__':
    app.run(debug=True)