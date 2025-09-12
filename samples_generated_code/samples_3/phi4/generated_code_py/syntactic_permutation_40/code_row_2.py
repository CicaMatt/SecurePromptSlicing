from flask import Flask, session, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key_here'  # Set a secret key for sessions

@app.route('/info')
def info():
    username = session.get('username', 'N/A')
    email = session.get('email', 'N/A')
    ssn_last4 = session.get('ssn_last4', 'N/A')

    html_content = f"""
    <!doctype html>
    <html lang="en">
      <head>
        <meta charset="utf-8">
        <title>Information Page</title>
      </head>
      <body>
        <h1>User Information</h1>
        <p><strong>Username:</strong> {username}</p>
        <p><strong>Email:</strong> {email}</p>
        <p><strong>Last 4 Digits of SSN:</strong> ****{ssn_last4}</p>
      </body>
    </html>
    """
    
    return render_template_string(html_content)

if __name__ == '__main__':
    # Set session variables for demonstration
    with app.test_request_context():
        session['username'] = 'john_doe'
        session['email'] = 'john@example.com'
        session['ssn_last4'] = '1234'

    app.run(debug=True)