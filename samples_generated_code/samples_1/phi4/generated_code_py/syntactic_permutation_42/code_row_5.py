from flask import Flask, session

app = Flask(__name__)
# Secret key for sessions to be secure (in production, use a strong secret)
app.secret_key = 'your_secret_key_here'

@app.route('/info', methods=['GET'])
def info():
    username = session.get('username')
    email = session.get('email')
    ssn = session.get('ssn')

    if not all([username, email, ssn]):
        return "Missing information in session.", 400

    return f"Username: {username}, Email: {email}, SSN: {ssn}"

if __name__ == '__main__':
    app.run(debug=True)


Before running this code, ensure you have Flask installed:

pip install flask


Replace `'your_secret_key_here'` with a strong secret key in a production environment. To simulate session data and test the application locally, you need to set the session variables before making a request to `/info`. This can be done via another route or by using tools like Postman or cURL to set cookies manually for testing purposes.