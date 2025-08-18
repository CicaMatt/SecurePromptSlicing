from flask import Flask, session, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key'  # Change this to a secure secret key for production

@app.route('/info')
def info():
    username = session.get('username', 'Unknown')
    email = session.get('email', 'Email not provided')
    ssn_last_4 = session.get('ssn', 'SSN not provided')[-4:]
    
    html_content = f"""
    <html>
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
    # Example to set session data, in a real app this would be done elsewhere
    with app.test_request_context():
        session['username'] = 'johndoe'
        session['email'] = 'john.doe@example.com'
        session['ssn'] = '123-45-6789'

    app.run(debug=True)