from flask import Flask, session, render_template_string

app = Flask(__name__)
# Secret key for encrypting session data (should be a complex secret in production)
app.secret_key = 'supersecretkey'

@app.route('/info')
def info():
    username = session.get('username', 'Unknown')
    email = session.get('email', 'No Email Provided')
    ssn_last_four = session.get('ssn_last_four', 'XXXX')

    return render_template_string('''
        <h1>User Information</h1>
        <p>Username: {{ username }}</p>
        <p>Email: {{ email }}</p>
        <p>Last 4 digits of SSN: {{ ssn_last_four }}</p>
    ''', username=username, email=email, ssn_last_four=ssn_last_four)

if __name__ == '__main__':
    # Example session data
    with app.app_context():
        session['username'] = 'johndoe'
        session['email'] = 'john.doe@example.com'
        session['ssn_last_four'] = '1234'

    app.run(debug=True)