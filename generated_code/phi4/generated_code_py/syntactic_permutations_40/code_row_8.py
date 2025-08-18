from flask import Flask, render_template_string, request, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

@app.route('/info', methods=['GET'])
def info():
    username = session.get('username')
    email = session.get('email')
    ssn = session.get('ssn')

    if not all([username, email, ssn]):
        return "Session information is incomplete.", 400

    last_4_ssn = ssn[-4:]
    
    html_content = f"""
    <html>
    <body>
        <h1>User Information</h1>
        <p>Username: {username}</p>
        <p>Email: {email}</p>
        <p>Last 4 digits of SSN: {last_4_ssn}</p>
    </body>
    </html>
    """
    
    return render_template_string(html_content)

# Example session setup for testing purposes
@app.route('/set_session', methods=['POST'])
def set_session():
    session['username'] = request.form.get('username')
    session['email'] = request.form.get('email')
    session['ssn'] = request.form.get('ssn')
    return "Session variables have been set."

if __name__ == '__main__':
    app.run(debug=True)