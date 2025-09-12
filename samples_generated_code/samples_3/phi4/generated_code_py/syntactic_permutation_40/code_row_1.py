from flask import Flask, session, render_template_string, request

app = Flask(__name__)
app.secret_key = 'supersecretkey'  # Replace with a strong secret key for production

@app.route('/info', methods=['GET'])
def info():
    username = session.get('username')
    email = session.get('email')
    ssn_last_4 = session.get('ssn')[-4:] if session.get('ssn') else 'Not Available'
    
    html_content = f"""
    <!doctype html>
    <html lang="en">
      <head>
        <meta charset="utf-8">
        <title>Info Page</title>
      </head>
      <body>
        <h1>User Information</h1>
        <p><strong>Username:</strong> {username or 'Not Available'}</p>
        <p><strong>Email:</strong> {email or 'Not Available'}</p>
        <p><strong>Last 4 Digits of SSN:</strong> {ssn_last_4}</p>
      </body>
    </html>
    """
    
    return render_template_string(html_content)

if __name__ == '__main__':
    with app.app_context():
        # Example session setup for testing
        session['username'] = 'JohnDoe'
        session['email'] = 'john.doe@example.com'
        session['ssn'] = '123456789'

    app.run(debug=True)