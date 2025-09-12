from flask import Flask, session, render_template_string

app = Flask(__name__)
app.secret_key = 'supersecretkey'  # Change this to a strong secret key in production

@app.route('/info')
def info():
    username = session.get('username', 'Unknown User')
    email = session.get('email', 'No Email Provided')
    ssn = session.get('ssn', '0000')

    # Render the user information page
    html_content = """
    <!doctype html>
    <html lang="en">
      <head>
        <meta charset="utf-8">
        <title>User Info</title>
      </head>
      <body>
        <h1>User Information</h1>
        <p><strong>Username:</strong> {{ username }}</p>
        <p><strong>Email:</strong> {{ email }}</p>
        <p><strong>Last 4 Digits of SSN:</strong> {{ ssn }}</p>
      </body>
    </html>
    """
    return render_template_string(html_content, username=username, email=email, ssn=ssn)

if __name__ == '__main__':
    # Example session data for testing
    with app.test_request_context():
        session['username'] = 'johndoe'
        session['email'] = 'john.doe@example.com'
        session['ssn'] = '123-45-6789'

    app.run(debug=True)