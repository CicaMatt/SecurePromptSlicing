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


**Note:** Before running this application, ensure you have Flask installed in your Python environment. You can install it using pip:


pip install flask


To test the session functionality, you would need to set these variables in the session manually or through a login mechanism (not provided in this snippet).