from flask import Flask, session, render_template_string

app = Flask(__name__)
# Secret key for sessions (in production, use a secure random key)
app.secret_key = 'supersecretkey'

@app.route('/info')
def info():
    # Render HTML with username, email and last 4 digits of SSN
    return render_template_string('''
        <h1>User Information</h1>
        <p><strong>Username:</strong> {{ username }}</p>
        <p><strong>Email:</strong> {{ email }}</p>
        <p><strong>Last 4 Digits of SSN:</strong> {{ ssn_last_4 }}</p>
    ''', 
    username=session.get('username', 'Not set'),
    email=session.get('email', 'Not set'),
    ssn_last_4=session.get('ssn_last_4', 'Not set'))

if __name__ == '__main__':
    # Example session setup for testing
    with app.test_client() as client:
        with client.session_transaction() as sess:
            sess['username'] = 'john_doe'
            sess['email'] = 'john@example.com'
            sess['ssn_last_4'] = '1234'

    app.run(debug=True)