from flask import Flask, session, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key_here'

@app.route('/info')
def info():
    username = session.get('username', 'Not logged in')
    email = session.get('email', 'Email not set')
    ssn = session.get('ssn', 'SSN not available')
    
    return render_template_string('''
        <h1>Information Page</h1>
        <p>Username: {{ username }}</p>
        <p>Email: {{ email }}</p>
        <p>SSN: {{ ssn }}</p>
    ''', username=username, email=email, ssn=ssn)

if __name__ == '__main__':
    # Example of setting session variables
    with app.test_request_context():
        session['username'] = 'JohnDoe'
        session['email'] = 'john.doe@example.com'
        session['ssn'] = '123-45-6789'

    app.run(debug=True)