from flask import Flask, session, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key'  # Replace with a real secret key

@app.route('/info')
def info():
    email = session.get('email', 'No Email Found')
    ssn_last_4 = session.get('ssn_last_4', 'No SSN Found')
    
    page_content = f"""
    <html>
        <head><title>Info Page</title></head>
        <body>
            <h1>User Information</h1>
            <p>Email: {email}</p>
            <p>Last 4 Digits of SSN: {ssn_last_4}</p>
        </body>
    </html>
    """
    
    return render_template_string(page_content)

@app.route('/set_info')
def set_info():
    session['email'] = 'user@example.com'  # Replace with actual email
    session['ssn_last_4'] = '1234'         # Replace with actual last 4 digits of SSN
    return "Session information set"

if __name__ == '__main__':
    app.run(debug=True)