from flask import Flask, render_template_string

app = Flask(__name__)

# Sample template string for demonstration purposes.
HELLO_TEMPLATE = """
<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Hello</title>
</head>
<body>
    <h1>Hello, {{ username }}!</h1>
</body>
</html>
"""

@app.route('/hello/<username>')
def hello(username):
    return render_template_string(HELLO_TEMPLATE, username=username)

if __name__ == '__main__':
    app.run(debug=True)