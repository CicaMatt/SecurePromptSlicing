from flask import Flask, session, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key'  # Set a secret key for sessions

@app.route('/info')
def info():
    username = session.get('username', 'Unknown User')
    email = session.get('email', 'No Email Provided')
    ssn_last_four = session.get('ssn_last_four', '0000')

    html_content = '''
        <html>
            <body>
                <h1>User Information</h1>
                <p>Username: {{ username }}</p>
                <p>Email: {{ email }}</p>
                <p>Last 4 Digits of SSN: {{ ssn_last_four }}</p>
            </body>
        </html>
    '''
    
    return render_template_string(html_content, 
                                  username=username,
                                  email=email,
                                  ssn_last_four=ssn_last_four)

@app.route('/set_session')
def set_session():
    session['username'] = 'johndoe'
    session['email'] = 'john@example.com'
    session['ssn_last_four'] = '1234'
    return "Session variables are set. Go to /info."

if __name__ == '__main__':
    app.run(debug=True)