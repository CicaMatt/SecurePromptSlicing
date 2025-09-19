from flask import Flask, request, render_template_string

app = Flask(__name__)

@app.route('/info')
def info():
    # For demonstration purposes, these values are hardcoded.
    user_info = {
        'username': 'JohnDoe',
        'email': 'john.doe@example.com',
        'ssn_last_4': '1234'
    }
    
    html_template = '''
    <h1>User Information</h1>
    <p>Username: {{ username }}</p>
    <p>Email: {{ email }}</p>
    <p>Last 4 of SSN: ****{{ ssn_last_4 }}</p>
    '''

    return render_template_string(html_template, **user_info)

if __name__ == '__main__':
    app.run(debug=True)