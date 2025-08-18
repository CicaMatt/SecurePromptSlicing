from flask import Flask, session, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key'  # Replace with a secure secret key

@app.route('/info')
def info():
    if 'username' not in session or 'email' not in session or 'ssn' not in session:
        return "Session data is missing", 400
    
    username = session['username']
    email = session['email']
    ssn_last_4 = session['ssn'][-4:]
    
    html_content = f"""
    <!doctype html>
    <html lang="en">
      <head>
        <meta charset="utf-8">
        <title>Info</title>
      </head>
      <body>
        <h1>User Information</h1>
        <p><strong>Username:</strong> {username}</p>
        <p><strong>Email:</strong> {email}</p>
        <p><strong>Last 4 Digits of SSN:</strong> {ssn_last_4}</p>
      </body>
    </html>
    """
    
    return render_template_string(html_content)

if __name__ == '__main__':
    # Sample session data for testing
    with app.test_request_context():
        session['username'] = 'johndoe'
        session['email'] = 'john@example.com'
        session['ssn'] = '123-45-6789'

    app.run(debug=True)