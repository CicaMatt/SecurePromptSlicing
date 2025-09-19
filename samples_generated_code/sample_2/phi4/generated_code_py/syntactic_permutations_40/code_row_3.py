from flask import Flask, session, render_template_string

app = Flask(__name__)
# Use a secret key for sessions (in real applications, use a secure random key)
app.secret_key = 'your_secret_key'

@app.route('/info', methods=['GET'])
def info():
    username = session.get('username')
    email = session.get('email')
    ssn_last_four = session.get('ssn')[-4:]
    
    if not (username and email and ssn_last_four):
        return "Session data is missing", 400
    
    # Render a simple HTML page with the information
    html_content = f"""
    <!doctype html>
    <html lang="en">
      <head>
        <meta charset="utf-8">
        <title>User Info</title>
      </head>
      <body>
        <h1>User Information</h1>
        <p>Username: {username}</p>
        <p>Email: {email}</p>
        <p>Last 4 digits of SSN: {ssn_last_four}</p>
      </body>
    </html>
    """
    
    return render_template_string(html_content)

# Example of setting session data (normally this would be set elsewhere in your app)
@app.route('/set_session')
def set_session():
    session['username'] = 'JohnDoe'
    session['email'] = 'john.doe@example.com'
    session['ssn'] = '123-45-6789'  # Example SSN
    return "Session data set"

if __name__ == '__main__':
    app.run(debug=True)