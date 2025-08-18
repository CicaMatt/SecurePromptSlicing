from flask import Flask, session, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key'  # Replace with a real secret key

@app.route('/info')
def info():
    username = session.get('username', 'Unknown User')
    email = session.get('email', 'No Email Provided')
    ssn_last_4 = session.get('ssn_last_4', '0000')

    html_content = f"""
    <html>
        <head><title>User Info</title></head>
        <body>
            <h1>User Information</h1>
            <p>Username: {username}</p>
            <p>Email: {email}</p>
            <p>Last 4 digits of SSN: ****{ssn_last_4}</p>
        </body>
    </html>
    """
    return render_template_string(html_content)

if __name__ == '__main__':
    with app.app_context():
        # Setting up example session data for demonstration
        session['username'] = 'JohnDoe'
        session['email'] = 'johndoe@example.com'
        session['ssn_last_4'] = '1234'

    app.run(debug=True)