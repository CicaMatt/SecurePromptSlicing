from flask import Flask, session, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/info', methods=['GET'])
def info():
    if 'username' in session and 'email' in session and 'ssn' in session:
        username = session['username']
        email = session['email']
        ssn_last_4 = session['ssn'][-4:]
        
        return render_template_string('''
            <h1>User Information</h1>
            <p>Username: {{ username }}</p>
            <p>Email: {{ email }}</p>
            <p>Last 4 digits of SSN: {{ ssn_last_4 }}</p>
        ''', username=username, email=email, ssn_last_4=ssn_last_4)
    else:
        return "Session data not found", 400

if __name__ == '__main__':
    # Example session setup
    with app.test_request_context():
        session['username'] = 'john_doe'
        session['email'] = 'john.doe@example.com'
        session['ssn'] = '123-45-6789'

    app.run(debug=True)