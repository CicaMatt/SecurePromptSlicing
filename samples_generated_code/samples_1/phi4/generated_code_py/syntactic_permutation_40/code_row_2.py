from flask import Flask, render_template_string

app = Flask(__name__)

# Dummy data representing user information
user_info = {
    'username': 'john_doe',
    'email': 'john.doe@example.com',
    'ssn': '123-45-6789'
}

@app.route('/info')
def info():
    # Extract the last 4 digits of SSN
    ssn_last_4 = user_info['ssn'].split('-')[-1]
    
    # HTML template as a string
    html_template = '''
    <!doctype html>
    <html lang="en">
      <head>
        <meta charset="utf-8">
        <title>User Information</title>
      </head>
      <body>
        <h1>User Information</h1>
        <p><strong>Username:</strong> {{ username }}</p>
        <p><strong>Email:</strong> {{ email }}</p>
        <p><strong>Last 4 digits of SSN:</strong> {{ ssn_last_4 }}</p>
      </body>
    </html>
    '''
    
    # Render the HTML with user data
    return render_template_string(html_template, username=user_info['username'], 
                                  email=user_info['email'], ssn_last_4=ssn_last_4)

if __name__ == '__main__':
    app.run(debug=True)