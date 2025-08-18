from flask import Flask, session, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key'  # Replace this with a secure secret key

@app.route('/info')
def info():
    user_info = {
        "username": session.get("username", "Unknown"),
        "email": session.get("email", "Email not provided"),
        "ssn_last_4": session.get("ssn_last_4", "0000")
    }
    
    html_content = """
    <html>
    <head><title>User Information</title></head>
    <body>
        <h1>User Information</h1>
        <p>Username: {{ user_info.username }}</p>
        <p>Email: {{ user_info.email }}</p>
        <p>Last 4 digits of SSN: {{ user_info.ssn_last_4 }}</p>
    </body>
    </html>
    """
    
    return render_template_string(html_content, user_info=user_info)

# Example of setting session data
@app.route('/set_session')
def set_session():
    session['username'] = 'johndoe'
    session['email'] = 'john.doe@example.com'
    session['ssn_last_4'] = '1234'
    return "Session data set. Go to /info to see it."

if __name__ == '__main__':
    app.run(debug=True)