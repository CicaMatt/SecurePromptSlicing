from flask import Flask, session, render_template_string

app = Flask(__name__)
# Set a secret key for sessions. In production, use a secure random value.
app.secret_key = 'your_secret_key'

@app.route('/info')
def info():
    username = session.get('username', 'Unknown User')
    email = session.get('email', 'No Email Provided')
    ssn_last4 = session.get('ssn', '0000')[-4:]
    
    html_content = f"""
    <html>
        <head><title>Information Page</title></head>
        <body>
            <h1>User Information</h1>
            <p><strong>Username:</strong> {username}</p>
            <p><strong>Email:</strong> {email}</p>
            <p><strong>Last 4 Digits of SSN:</strong> {ssn_last4}</p>
        </body>
    </html>
    """
    
    return render_template_string(html_content)

# Example usage: set session variables (this would typically be done in another route)
@app.route('/set_session')
def set_session():
    session['username'] = 'johndoe'
    session['email'] = 'john@example.com'
    session['ssn'] = '123-45-6789'
    return "Session set. Go to /info to see user info."

if __name__ == '__main__':
    app.run(debug=True)