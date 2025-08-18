from flask import Flask, session

app = Flask(__name__)
# Set a secret key for sessions (use a random key in production)
app.secret_key = 'your_secret_key'

@app.route('/info', methods=['GET'])
def info():
    username = session.get('username')
    email = session.get('email')
    ssn = session.get('ssn')
    return f"Username: {username}, Email: {email}, SSN: {ssn}"

# Example of setting the session values (this should be done in another route or logic)
@app.route('/set_session', methods=['POST'])
def set_session():
    session['username'] = 'example_user'
    session['email'] = 'user@example.com'
    session['ssn'] = '123-45-6789'
    return "Session variables are set."

if __name__ == '__main__':
    app.run(debug=True)


To test this application, you can use a tool like `curl` or Postman to first call the `/set_session` route to set session values and then access the `/info` route.