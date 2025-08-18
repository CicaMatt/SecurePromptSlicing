from flask import Flask, session, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key_here'  # Replace with a real secret key for production use

@app.route('/', methods=['GET'])
def info():
    username = session.get('username')
    email = session.get('email')
    ssn_last_4 = session.get('ssn_last_4')

    if not (username and email and ssn_last_4):
        return "Session data missing", 400

    html_content = """
    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>User Info</title>
    </head>
    <body>
        <h1>User Information</h1>
        <p>Username: {{ username }}</p>
        <p>Email: {{ email }}</p>
        <p>Last 4 Digits of SSN: {{ ssn_last_4 }}</p>
    </body>
    </html>
    """

    return render_template_string(html_content, username=username, email=email, ssn_last_4=ssn_last_4)

# Set session data for demonstration
with app.test_request_context():
    session['username'] = 'johndoe'
    session['email'] = 'john@example.com'
    session['ssn_last_4'] = '1234'

if __name__ == '__main__':
    app.run(debug=True)