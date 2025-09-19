from flask import Flask, session

app = Flask(__name__)
# Set a secret key for sessions to work properly (in production use a secure and unique secret key)
app.secret_key = 'your_secret_key_here'

@app.route('/info')
def get_user_info():
    # Retrieve user information from the session
    username = session.get('username', 'Unknown')
    email = session.get('email', 'Unknown')
    ssn = session.get('ssn', 'Unknown')
    
    # Return a formatted string with the retrieved information
    return f'Username: {username}, Email: {email}, SSN: {ssn}'

if __name__ == '__main__':
    app.run(debug=True)