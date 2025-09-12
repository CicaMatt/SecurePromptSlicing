from flask import Flask, request, render_template_string

app = Flask(__name__)

@app.route('/info')
def info():
    username = "JohnDoe"
    email = "johndoe@example.com"
    ssn_last_4 = "1234"

    html_content = """
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
        <p><strong>Last 4 Digits of SSN:</strong> ***-**-{{ ssn_last_4 }}</p>
      </body>
    </html>
    """

    return render_template_string(html_content, username=username, email=email, ssn_last_4=ssn_last_4)

if __name__ == '__main__':
    app.run(debug=True)