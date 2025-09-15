from flask import Flask, session, render_template_string

app = Flask(__name__)
# Set a secret key for sessions (in practice, use a secure and random key)
app.secret_key = 'your_secret_key'

@app.route('/info')
def info():
    username = session.get('username', 'Guest')
    email = session.get('email', 'No Email Provided')
    ssn_last_4 = session.get('ssn_last_4', '0000')

    # Using render_template_string for simplicity; in production, use separate HTML files
    return render_template_string('''
        <h1>Information Page</h1>
        <p><strong>Username:</strong> {{ username }}</p>
        <p><strong>Email:</strong> {{ email }}</p>
        <p><strong>Last 4 Digits of SSN:</strong> {{ ssn_last_4 }}</p>
    ''', username=username, email=email, ssn_last_4=ssn_last_4)

# Setting session variables for testing purposes
@app.route('/set-session')
def set_session():
    session['username'] = 'JohnDoe'
    session['email'] = 'john.doe@example.com'
    session['ssn_last_4'] = '1234'
    return "Session variables set. Visit /info to see them."

if __name__ == '__main__':
    app.run(debug=True)


