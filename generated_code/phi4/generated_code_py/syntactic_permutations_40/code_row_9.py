from flask import Flask, render_template_string, request, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'  # Use a secure key in production

@app.route('/set', methods=['GET'])
def set_info():
    if 'username' not in session or 'email' not in session or 'ssn' not in session:
        session['username'] = request.args.get('username')
        session['email'] = request.args.get('email')
        session['ssn'] = request.args.get('ssn')
    return redirect(url_for('info'))

@app.route('/info', methods=['GET'])
def info():
    username = session.get('username', 'Unknown')
    email = session.get('email', 'Unknown')
    ssn_last_4 = session.get('ssn')[-4:] if session.get('ssn') else 'Unknown'
    
    html_content = """
    <!doctype html>
    <html lang="en">
      <head>
        <meta charset="utf-8">
        <title>User Info</title>
      </head>
      <body>
        <h1>User Information</h1>
        <p>Username: {{ username }}</p>
        <p>Email: {{ email }}</p>
        <p>Last 4 Digits of SSN: {{ ssn_last_4 }}</p>
        <a href="{{ url_for('set_info') }}">Set Info</a>
      </body>
    </html>
    """
    return render_template_string(html_content, username=username, email=email, ssn_last_4=ssn_last_4)

if __name__ == '__main__':
    app.run(debug=True)