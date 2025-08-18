from flask import Flask, session, render_template_string

app = Flask(__name__)
app.secret_key = 'supersecretkey'

@app.route('/info')
def info():
    if 'username' not in session or 'email' not in session or 'ssn' not in session:
        return "Session data missing", 400
    
    username = session['username']
    email = session['email']
    ssn_last_4 = session['ssn'][-4:]
    
    html_content = f"""
    <html>
        <head><title>Info Page</title></head>
        <body>
            <h1>User Information</h1>
            <p>Username: {username}</p>
            <p>Email: {email}</p>
            <p>Last 4 digits of SSN: {ssn_last_4}</p>
        </body>
    </html>
    """
    
    return render_template_string(html_content)

if __name__ == '__main__':
    # Example session data for testing
    with app.test_request_context():
        session['username'] = 'johndoe'
        session['email'] = 'john.doe@example.com'
        session['ssn'] = '123-45-6789'

    app.run(debug=True)