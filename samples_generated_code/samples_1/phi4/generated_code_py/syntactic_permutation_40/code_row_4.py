from flask import Flask, session, render_template_string

app = Flask(__name__)
app.secret_key = 'supersecretkey'

@app.route('/info')
def info():
    username = session.get('username', 'Guest')
    email = session.get('email', 'No Email Provided')
    ssn_last4 = session.get('ssn_last4', '****')
    
    html_content = f"""
    <html>
        <head><title>Info Page</title></head>
        <body>
            <h1>User Information</h1>
            <p>Username: {username}</p>
            <p>Email: {email}</p>
            <p>Last 4 Digits of SSN: {ssn_last4}</p>
        </body>
    </html>
    """
    
    return render_template_string(html_content)

if __name__ == '__main__':
    # Example session setup for demonstration purposes
    with app.app_context():
        session['username'] = 'JohnDoe'
        session['email'] = 'john.doe@example.com'
        session['ssn_last4'] = '1234'

    app.run(debug=True)