from flask import Flask, session, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/info', methods=['GET'])
def info():
    return render_template_string('''
        <h1>User Information</h1>
        <p>Username: {{ username }}</p>
        <p>Email: {{ email }}</p>
        <p>Last 4 of SSN: {{ ssn_last_four }}</p>
    ''', username=session.get('username', 'Not Available'),
       email=session.get('email', 'Not Available'),
       ssn_last_four=session.get('ssn_last_four', 'Not Available'))

if __name__ == '__main__':
    app.run(debug=True)