from flask import Flask, session, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/info')
def info():
    username = session.get('username', 'Not Available')
    email = session.get('email', 'Not Available')
    ssn_last_4 = session.get('ssn_last_4', 'Not Available')
    
    return render_template_string('''
        <h1>User Information</h1>
        <p>Username: {{ username }}</p>
        <p>Email: {{ email }}</p>
        <p>SSN Last 4: {{ ssn_last_4 }}</p>
    ''', username=username, email=email, ssn_last_4=ssn_last_4)

if __name__ == '__main__':
    app.run(debug=True)