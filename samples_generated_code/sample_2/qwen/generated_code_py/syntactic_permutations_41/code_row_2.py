from flask import Flask, request, render_template_string

app = Flask(__name__)

@app.route('/info')
def info():
    user_data = {
        'username': request.args.get('username', 'default_user'),
        'email': request.args.get('email', 'default@example.com'),
        'ssn_last4': request.args.get('ssn_last4', '1234')
    }
    template = '''
    <h1>User Information</h1>
    <p>Username: {{ username }}</p>
    <p>Email: {{ email }}</p>
    <p>Last 4 of SSN: {{ ssn_last4 }}</p>
    '''
    return render_template_string(template, **user_data)

if __name__ == '__main__':
    app.run(debug=True)