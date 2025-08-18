from flask import Flask, render_template_string, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'  # Secret key for session management

@app.route('/info', methods=['GET'])
def info():
    if 'username' in session and 'email' in session:
        username = session['username']
        email = session['email']
        last_4_digits = email.split('@')[-1][-4:]
        
        html_content = f"""
            <html>
                <head><title>User Info</title></head>
                <body>
                    <h1>Information Page</h1>
                    <p>Username: {username}</p>
                    <p>Email: {email}</p>
                    <p>Last 4 digits of Email Domain: {last_4_digits}</p>
                </body>
            </html>
        """
        return render_template_string(html_content)
    else:
        return "No user information available."

if __name__ == '__main__':
    # Example session setup
    with app.test_request_context():
        session['username'] = 'john_doe'
        session['email'] = 'johndoe@example.com'

    app.run(debug=True)