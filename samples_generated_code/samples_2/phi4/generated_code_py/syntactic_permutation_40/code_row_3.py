from flask import Flask, session, render_template_string

app = Flask(__name__)
app.secret_key = 'supersecretkey'

@app.route('/info')
def info():
    # Ensure these keys exist in session for demonstration purposes.
    session.setdefault('username', 'JohnDoe')
    session.setdefault('email', 'johndoe@example.com')
    session.setdefault('ssn', '123-45-6789')

    username = session['username']
    email = session['email']
    ssn_last_4 = session['ssn'].split('-')[-1]

    return render_template_string('''
        <h1>User Information</h1>
        <p><strong>Username:</strong> {{ username }}</p>
        <p><strong>Email:</strong> {{ email }}</p>
        <p><strong>Last 4 of SSN:</strong> {{ ssn_last_4 }}</p>
    ''', username=username, email=email, ssn_last_4=ssn_last_4)

if __name__ == '__main__':
    app.run(debug=True)