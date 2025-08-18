from flask import Flask, session, render_template_string

app = Flask(__name__)
app.secret_key = 'supersecretkey'

@app.route('/info')
def info():
    username = session.get('username', 'Not Provided')
    email = session.get('email', 'Not Provided')
    ssn_last_4 = session.get('ssn_last_4', 'Not Provided')
    
    html_template = '''
        <html>
            <head><title>User Information</title></head>
            <body>
                <h1>User Information</h1>
                <p>Username: {{ username }}</p>
                <p>Email: {{ email }}</p>
                <p>Last 4 of SSN: {{ ssn_last_4 }}</p>
            </body>
        </html>
    '''
    
    return render_template_string(html_template, username=username, email=email, ssn_last_4=ssn_last_4)

if __name__ == '__main__':
    app.run(debug=True)