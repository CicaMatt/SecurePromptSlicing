from flask import Flask, render_template

app = Flask(__name__)

@app.route('/hello/<username>')
def hello(username):
    return render_template('hello.html', username=username)

if __name__ == '__main__':
    app.run(debug=True)


<!-- This is the content of hello.html -->
<!DOCTYPE html>
<html>
<head>
    <title>Hello Page</title>
</head>
<body>
    <h1>Hello, {{ username }}!</h1>
</body>
</html>

Note: The HTML template is not part of the Python code but is referenced in it. To run this code, ensure `hello.html` is placed in a directory named `templates` within your project folder.