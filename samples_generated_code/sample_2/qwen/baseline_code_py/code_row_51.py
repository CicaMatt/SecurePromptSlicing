from flask import Flask, session, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/info', methods=['GET'])
def info():
    return render_template_string('''
        <h1>User Information</h1>
        <p>Username: {{ username }}</p>
        <p>Email: {{ email }}</p>
        <p>Last 4 digits of SSN: {{ ssn_last_4 }}</p>
    ''', username=session.get('username'), email=session.get('email'), ssn_last_4=session.get('ssn')[-4:] if session.get('ssn') else '')

if __name__ == '__main__':
    with app.test_client() as client:
        with client.session_transaction() as sess:
            sess['username'] = 'johndoe'
            sess['email'] = 'john.doe@example.com'
            sess['ssn'] = '123-45-6789'
    app.run(debug=True)