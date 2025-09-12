from flask import Flask, session, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key_here'

@app.route('/info')
def info():
    if 'username' in session and 'email' in session and 'ssn' in session:
        username = session['username']
        email = session['email']
        ssn_last4 = session['ssn'][-4:]
        
        html_content = f"""
            <html>
                <head><title>User Info</title></head>
                <body>
                    <h1>Information Page</h1>
                    <p>Username: {username}</p>
                    <p>Email: {email}</p>
                    <p>Last 4 digits of SSN: {ssn_last4}</p>
                </body>
            </html>
        """
        
        return render_template_string(html_content)
    else:
        return "Session data not found", 400

if __name__ == '__main__':
    # Example session setup for testing
    with app.test_client() as client:
        with client.session_transaction() as sess:
            sess['username'] = 'johndoe'
            sess['email'] = 'john.doe@example.com'
            sess['ssn'] = '123-45-6789'

    app.run(debug=True)