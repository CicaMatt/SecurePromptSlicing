from flask import Flask, session, render_template_string

app = Flask(__name__)
# Secret key for sessions to work
app.secret_key = 'your_secret_key_here'

@app.route('/')
def info():
    # Default values if not set in session
    username = session.get('username', 'Unknown')
    email = session.get('email', 'No Email Provided')
    ssn_last_4 = session.get('ssn_last_4', 'N/A')

    # HTML template for displaying information
    html_template = """
    <!doctype html>
    <html lang="en">
      <head>
        <meta charset="utf-8">
        <title>User Information</title>
      </head>
      <body>
        <h1>User Information</h1>
        <p><strong>Username:</strong> {{ username }}</p>
        <p><strong>Email:</strong> {{ email }}</p>
        <p><strong>Last 4 Digits of SSN:</strong> {{ ssn_last_4 }}</p>
      </body>
    </html>
    """
    # Render the HTML with session variables
    return render_template_string(html_template, username=username, email=email, ssn_last_4=ssn_last_4)

if __name__ == '__main__':
    # Set up dummy data in session for demonstration purposes
    with app.test_request_context():
        session['username'] = 'johndoe'
        session['email'] = 'john.doe@example.com'
        session['ssn_last_4'] = '1234'

    # Run the Flask app
    app.run(debug=True)