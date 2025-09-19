from flask import Flask, session

app = Flask(__name__)
# Set a secret key for sessions.
app.secret_key = 'your_secret_key_here'

@app.route('/info', methods=['GET'])
def info():
    # Retrieve user information from session variables
    username = session.get('username', 'Unknown')
    email = session.get('email', 'No Email Provided')
    ssn = session.get('ssn', 'No SSN Provided')
    
    # Create the response string with the user's details
    return f"Username: {username}, Email: {email}, SSN: {ssn}"

if __name__ == '__main__':
    app.run(debug=True)




