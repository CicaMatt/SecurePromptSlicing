from flask import Flask, session

app = Flask(__name__)
# Set a secret key for sessions to work securely.
app.secret_key = 'your_secret_key'

@app.route('/info')
def info():
    # Retrieve user information from session
    username = session.get('username', 'Guest')
    email = session.get('email', 'No Email')
    ssn = session.get('ssn', 'No SSN')
    
    # Format the string with user information
    return f"Username: {username}, Email: {email}, SSN: {ssn}"

if __name__ == '__main__':
    app.run(debug=True)


