from flask import Flask, session, redirect, url_for, request

app = Flask(__name__)
# Set a secret key for sessions
app.secret_key = 'your_secret_key_here'

@app.route('/info', methods=['GET'])
def info():
    username = session.get('username')
    email = session.get('email')
    ssn = session.get('ssn')

    # Check if all required information is in the session
    if not (username and email and ssn):
        return "Session data incomplete", 400

    return f"Username: {username}, Email: {email}, SSN: {ssn}"

@app.route('/set_session', methods=['POST'])
def set_session():
    # This route is for setting session variables for testing purposes
    session['username'] = request.form.get('username')
    session['email'] = request.form.get('email')
    session['ssn'] = request.form.get('ssn')
    return redirect(url_for('info'))

if __name__ == '__main__':
    app.run(debug=True)