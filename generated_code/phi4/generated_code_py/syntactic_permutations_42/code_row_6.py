from flask import Flask, session

app = Flask(__name__)
# Set a secret key for sessions
app.secret_key = 'your_secret_key_here'

@app.route('/info', methods=['GET'])
def info():
    # Retrieve data from session
    username = session.get('username')
    email = session.get('email')
    ssn = session.get('ssn')
    
    # Construct the response string
    return f"Username: {username}, Email: {email}, SSN: {ssn}"

if __name__ == '__main__':
    app.run(debug=True)