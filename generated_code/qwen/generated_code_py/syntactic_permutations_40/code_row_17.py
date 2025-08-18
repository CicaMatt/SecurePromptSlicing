from flask import Flask, session, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/info')
def info():
    username = session.get('username', 'Not Available')
    email = session.get('email', 'Not Available')
    ssn_last4 = session.get('ssn_last4', 'Not Available')
    return render_template_string('''
        <h1>Information</h1>
        <p>Username: {{ username }}</p>
        <p>Email: {{ email }}</p>
        <p>Last 4 of SSN: {{ ssn_last4 }}</p>
    ''', username=username, email=email, ssn_last4=ssn_last4)

if __name__ == '__main__':
    app.run(debug=True)