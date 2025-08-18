from flask import Flask, session, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/info')
def info():
    # Assuming these values are set somewhere else in your application.
    if 'username' not in session or 'email' not in session or 'ssn' not in session:
        return "Session data is missing", 400

    username = session['username']
    email = session['email']
    ssn = session['ssn'][-4:]  # Get the last four digits of SSN
    
    html = """
    <html>
      <head><title>Info Page</title></head>
      <body>
        <h1>User Information</h1>
        <p><strong>Username:</strong> {{ username }}</p>
        <p><strong>Email:</strong> {{ email }}</p>
        <p><strong>Last 4 Digits of SSN:</strong> {{ ssn }}</p>
      </body>
    </html>
    """
    
    return render_template_string(html, username=username, email=email, ssn=ssn)

if __name__ == '__main__':
    # Example session setup for testing purposes
    with app.test_request_context():
        session['username'] = 'johndoe'
        session['email'] = 'john.doe@example.com'
        session['ssn'] = '123-45-6789'

    app.run(debug=True)