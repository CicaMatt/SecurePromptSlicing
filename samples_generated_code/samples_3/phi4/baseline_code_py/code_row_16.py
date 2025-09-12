from flask import Flask, request, render_template_string

app = Flask(__name__)

@app.route('/info')
def info():
    # Simulated user data
    username = "JohnDoe"
    email = "john.doe@example.com"
    ssn_last_four = "1234"

    # HTML template for displaying information
    html_content = """
    <!doctype html>
    <html lang="en">
      <head>
        <meta charset="utf-8">
        <title>User Info</title>
      </head>
      <body>
        <h1>User Information</h1>
        <p><strong>Username:</strong> {{ username }}</p>
        <p><strong>Email:</strong> {{ email }}</p>
        <p><strong>Last 4 of SSN:</strong> ****{{ ssn_last_four }}</p>
      </body>
    </html>
    """

    return render_template_string(html_content, username=username, email=email, ssn_last_four=ssn_last_four)

if __name__ == '__main__':
    app.run(debug=True)