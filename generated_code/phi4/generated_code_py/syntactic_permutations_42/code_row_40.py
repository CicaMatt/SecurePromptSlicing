from flask import Flask, session

app = Flask(__name__)
# Set a secret key for sessions
app.secret_key = 'your_secret_key'

@app.route('/info')
def info():
    # Retrieve information from session
    username = session.get('username', 'Guest')
    email = session.get('email', 'No Email Provided')
    ssn = session.get('ssn', 'SSN Not Available')

    # Construct the response string
    response = f"Username: {username}, Email: {email}, SSN: {ssn}"
    
    return response

if __name__ == '__main__':
    app.run(debug=True)