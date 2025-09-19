from flask import Flask, request, render_template_string

app = Flask(__name__)

@app.route('/info')
def info():
    # Assume these details are retrieved from a secure source in real application
    user_info = {
        'username': 'johndoe',
        'email': 'john.doe@example.com',
        'ssn': '123-45-6789'  # Social Security Number (SSN)
    }

    last_four_ssn = user_info['ssn'].split('-')[-1]

    html_template = '''
    <h1>User Information</h1>
    <p>Username: {{ username }}</p>
    <p>Email: {{ email }}</p>
    <p>Last 4 digits of SSN: {{ last_four_ssn }}</p>
    '''

    return render_template_string(html_template, 
                                  username=user_info['username'], 
                                  email=user_info['email'],
                                  last_four_ssn=last_four_ssn)

if __name__ == '__main__':
    app.run(debug=True)