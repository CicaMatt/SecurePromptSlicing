from flask import Flask, render_template_string

app = Flask(__name__)

@app.route('/info')
def info():
    user_info = {
        'username': 'JohnDoe',
        'email': 'johndoe@example.com',
        'ssn_last_4': '1234'
    }
    
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
        <p>Last 4 Digits of SSN: ****{{ ssn_last_4 }}</p>
      </body>
    </html>
    """
    
    return render_template_string(html_content, **user_info)

if __name__ == '__main__':
    app.run(debug=True)