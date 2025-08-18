from flask import Flask, request, render_template_string

app = Flask(__name__)

@app.route('/info', methods=['GET'])
def info():
    username = request.args.get('username', 'Guest')
    email = request.args.get('email', 'No Email Provided')
    last4_digits = request.args.get('last4digits', '0000')

    html_content = f"""
    <!doctype html>
    <html lang="en">
      <head>
        <meta charset="utf-8">
        <title>User Information</title>
      </head>
      <body>
        <h1>User Information</h1>
        <p><strong>Username:</strong> {username}</p>
        <p><strong>Email:</strong> {email}</p>
        <p><strong>Last 4 Digits:</strong> {last4_digits}</p>
      </body>
    </html>
    """
    
    return render_template_string(html_content)

if __name__ == '__main__':
    app.run(debug=True)