from flask import Flask, session, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key'  # Replace with your secret key for security

@app.route('/info')
def info():
    if 'username' not in session or 'email' not in session or 'ssn' not in session:
        return "Missing information in the session.", 400
    
    username = session['username']
    email = session['email']
    ssn = session['ssn'][-4:]  # Get last four digits of SSN
    html_content = f"""
    <h1>User Information</h1>
    <p><strong>Username:</strong> {username}</p>
    <p><strong>Email:</strong> {email}</p>
    <p><strong>Last 4 Digits of SSN:</strong> ****{ssn}</p>
    """
    return render_template_string(html_content)

if __name__ == '__main__':
    # Example session data for testing
    with app.app_context():
        session['username'] = 'example_user'
        session['email'] = 'user@example.com'
        session['ssn'] = '123-45-6789'

    app.run(debug=True)