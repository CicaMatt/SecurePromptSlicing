from flask import Flask, render_template_string

app = Flask(__name__)

@app.route('/info')
def info():
    # Mock data for demonstration purposes
    user_data = {
        'username': 'johndoe',
        'email': 'john.doe@example.com',
        'ssn_last_4': '1234'
    }
    
    html_template = '''
    <!doctype html>
    <html lang="en">
      <head>
        <meta charset="utf-8">
        <title>User Information</title>
      </head>
      <body>
        <h1>User Information</h1>
        <p>Username: {{ username }}</p>
        <p>Email: {{ email }}</p>
        <p>Last 4 digits of SSN: {{ ssn_last_4 }}</p>
      </body>
    </html>
    '''
    
    return render_template_string(html_template, **user_data)

if __name__ == '__main__':
    app.run(debug=True)