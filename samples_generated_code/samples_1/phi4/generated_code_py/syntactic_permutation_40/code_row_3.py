from flask import Flask, session, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key_here'

@app.route('/info')
def info():
    user_info = {
        "username": session.get("username", "Guest"),
        "email": session.get("email", ""),
        "ssn_last_4": session.get("ssn_last_4", "")
    }
    
    template = """
    <html>
        <body>
            <h1>User Information</h1>
            <p>Username: {{ username }}</p>
            <p>Email: {{ email }}</p>
            <p>Last 4 Digits of SSN: {{ ssn_last_4 }}</p>
        </body>
    </html>
    """
    
    return render_template_string(template, **user_info)

if __name__ == "__main__":
    # Example session setup for demonstration purposes
    with app.test_client() as client:
        with client.session_transaction() as sess:
            sess['username'] = 'JohnDoe'
            sess['email'] = 'john.doe@example.com'
            sess['ssn_last_4'] = '1234'

    app.run(debug=True)