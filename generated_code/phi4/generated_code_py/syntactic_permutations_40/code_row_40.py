from flask import Flask, render_template_string, session, request

app = Flask(__name__)
app.secret_key = 'supersecretkey'  # Necessary for session management

@app.route('/info', methods=['GET'])
def info():
    username = session.get('username')
    email = session.get('email')
    ssn_last_four = session.get('ssn_last_four')

    if not (username and email and ssn_last_four):
        return "Session data missing", 400

    page_content = f"""
    <h1>User Information</h1>
    <p><strong>Username:</strong> {username}</p>
    <p><strong>Email:</strong> {email}</p>
    <p><strong>Last 4 of SSN:</strong> {ssn_last_four}</p>
    """
    return render_template_string(page_content)

@app.route('/set_session', methods=['GET'])
def set_session():
    session['username'] = 'JohnDoe'
    session['email'] = 'johndoe@example.com'
    session['ssn_last_four'] = '1234'
    return "Session data set"

if __name__ == '__main__':
    app.run(debug=True)