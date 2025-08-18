from flask import Flask, session, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key'  # Replace with a secure secret key

@app.route('/info')
def info():
    if 'username' in session and 'email' in session and 'ssn' in session:
        username = session['username']
        email = session['email']
        ssn_last_4 = session['ssn'][-4:]
        
        html_content = f"""
            <html>
                <head><title>User Info</title></head>
                <body>
                    <h1>User Information</h1>
                    <p>Username: {username}</p>
                    <p>Email: {email}</p>
                    <p>Last 4 digits of SSN: {ssn_last_4}</p>
                </body>
            </html>
        """
        return render_template_string(html_content)
    else:
        return 'Session variables not set.', 400

# Example to set session data (for testing purpose, usually handled differently in real applications)
@app.route('/set_session')
def set_session():
    session['username'] = 'john_doe'
    session['email'] = 'john.doe@example.com'
    session['ssn'] = '123456789'
    return 'Session variables set.'

if __name__ == '__main__':
    app.run(debug=True)