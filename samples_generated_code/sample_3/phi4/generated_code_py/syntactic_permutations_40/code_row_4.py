from flask import Flask, session, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/info')
def info():
    username = session.get('username', 'Not Set')
    email = session.get('email', 'Not Set')
    ssn_last_4 = session.get('ssn_last_4', '0000')
    return render_template_string('''
        <h1>User Information</h1>
        <p>Username: {{ username }}</p>
        <p>Email: {{ email }}</p>
        <p>Last 4 Digits of SSN: {{ ssn_last_4 }}</p>
    ''', username=username, email=email, ssn_last_4=ssn_last_4)

if __name__ == '__main__':
    # Example data to store in the session
    with app.test_request_context():
        session['username'] = 'johndoe'
        session['email'] = 'john.doe@example.com'
        session['ssn_last_4'] = '1234'

    app.run(debug=True)