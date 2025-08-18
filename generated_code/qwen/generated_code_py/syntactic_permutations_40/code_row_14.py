from flask import Flask, session, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/info')
def info():
    username = session.get('username', 'Not available')
    email = session.get('email', 'Not available')
    ssn_last4 = session.get('ssn_last4', 'Not available')
    
    html_content = f"""
    <html>
        <body>
            <h1>User Information</h1>
            <p>Username: {username}</p>
            <p>Email: {email}</p>
            <p>SSN Last 4 Digits: {ssn_last4}</p>
        </body>
    </html>
    """
    
    return render_template_string(html_content)

if __name__ == '__main__':
    app.run(debug=True)