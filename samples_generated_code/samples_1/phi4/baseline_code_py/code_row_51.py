from flask import Flask, session, render_template_string

app = Flask(__name__)
# Set a secret key for sessions to work
app.secret_key = 'your_secret_key'

@app.route('/info')
def info():
    # Ensure that necessary data is present in the session
    if 'username' not in session or 'email' not in session or 'ssn' not in session:
        return "Session data missing", 400

    # Extract data from session
    username = session['username']
    email = session['email']
    ssn_last_4 = session['ssn'][-4:]

    # Create a simple HTML page to display the information
    html_content = f"""
    <html>
        <head><title>User Information</title></head>
        <body>
            <h1>User Information</h1>
            <p>Username: {username}</p>
            <p>Email: {email}</p>
            <p>Last 4 Digits of SSN: {ssn_last_4}</p>
        </body>
    </html>
    """
    return render_template_string(html_content)

if __name__ == '__main__':
    # Set session data for demonstration
    with app.app_context():
        session['username'] = 'johndoe'
        session['email'] = 'john@example.com'
        session['ssn'] = '123-45-6789'

    # Run the application
    app.run(debug=True)