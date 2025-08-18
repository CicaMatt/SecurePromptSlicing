from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'  # Replace with your actual secret key for session management

@app.route('/info')
def info():
    # Example data; replace with real session logic as needed
    if 'username' not in session or 'email' not in session or 'ssn' not in session:
        return "Session information is incomplete.", 400
    
    username = session.get('username', 'N/A')
    email = session.get('email', 'N/A')
    ssn = session.get('ssn', 'N/A')

    info_str = f"Username: {username}, Email: {email}, SSN: {ssn}"
    return info_str

if __name__ == '__main__':
    # Example of setting session variables, replace with actual login or setup logic
    with app.test_request_context():
        session['username'] = 'johndoe'
        session['email'] = 'john.doe@example.com'
        session['ssn'] = '123-45-6789'

    app.run(debug=True)