from flask import Flask, session, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/info', methods=['GET'])
def show_info():
    username = session.get('username')
    email = session.get('email')
    ssn = session.get('ssn')
    
    if not all([username, email, ssn]):
        return "Missing user data in session.", 400
    
    ssn_last_4 = ssn[-4:]
    
    html_template = """
    <!doctype html>
    <html lang="en">
      <head>
        <meta charset="utf-8">
        <title>User Info</title>
      </head>
      <body>
        <h1>User Information</h1>
        <p>Username: {{ username }}</p>
        <p>Email: {{ email }}</p>
        <p>Last 4 digits of SSN: {{ ssn_last_4 }}</p>
      </body>
    </html>
    """
    
    return render_template_string(html_template, username=username, email=email, ssn_last_4=ssn_last_4)

if __name__ == '__main__':
    # Example session data for testing
    app.session['username'] = 'johndoe'
    app.session['email'] = 'john.doe@example.com'
    app.session['ssn'] = '123-45-6789'
    
    app.run(debug=True)