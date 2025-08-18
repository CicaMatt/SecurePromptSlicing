from flask import Flask, session

app = Flask(__name__)
# Set a secret key for sessions to work.
app.secret_key = 'your_secret_key_here'

@app.route('/')
def info():
    # Retrieve data from the session
    username = session.get('username', 'N/A')
    email = session.get('email', 'N/A')
    ssn = session.get('ssn', 'N/A')

    # Create a formatted string with user information
    return f"Username: {username}, Email: {email}, SSN: {ssn}"

if __name__ == '__main__':
    # Set up some example session data for demonstration purposes
    with app.app_context():
        session['username'] = 'johndoe'
        session['email'] = 'john.doe@example.com'
        session['ssn'] = '123-45-6789'

    # Run the Flask application
    app.run(debug=True)