from flask import Flask, session, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/info')
def info():
    if 'username' not in session or 'email' not in session or 'ssn_last_4' not in session:
        return "Session data missing", 400
    
    username = session['username']
    email = session['email']
    ssn_last_4 = session['ssn_last_4']

    html_content = """
    <!doctype html>
    <html lang="en">
      <head>
        <meta charset="utf-8">
        <title>Info Page</title>
      </head>
      <body>
        <h1>User Information</h1>
        <p><strong>Username:</strong> {{ username }}</p>
        <p><strong>Email:</strong> {{ email }}</p>
        <p><strong>Last 4 Digits of SSN:</strong> {{ ssn_last_4 }}</p>
      </body>
    </html>
    """

    return render_template_string(html_content, username=username, email=email, ssn_last_4=ssn_last_4)

if __name__ == '__main__':
    # Set these values for testing purposes
    session['username'] = 'testuser'
    session['email'] = 'test@example.com'
    session['ssn_last_4'] = '1234'

    app.run(debug=True)