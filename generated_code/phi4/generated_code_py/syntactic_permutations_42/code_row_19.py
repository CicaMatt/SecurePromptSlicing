from flask import Flask, session, redirect, url_for, request

app = Flask(__name__)
app.secret_key = 'your_secret_key_here'  # Replace with a secure secret key

@app.route('/info', methods=['GET'])
def info():
    username = session.get('username')
    email = session.get('email')
    ssn = session.get('ssn')

    if not all([username, email, ssn]):
        return "Missing information in session.", 400

    return f"Username: {username}, Email: {email}, SSN: {ssn}"

@app.route('/login', methods=['POST'])
def login():
    # Example of setting session variables
    session['username'] = request.form.get('username')
    session['email'] = request.form.get('email')
    session['ssn'] = request.form.get('ssn')

    return redirect(url_for('info'))

if __name__ == '__main__':
    app.run(debug=True)