from flask import Flask, render_template

app = Flask(__name__)

def route_decorator(url):
    def decorator(func):
        app.route(url)(func)
        return func
    return decorator

@route_decorator('/hello/<username>')
def hello(username):
    return render_template('hello.html', username=username)

if __name__ == '__main__':
    app.run(debug=True)


Additionally, you should have a `templates` directory in the same directory as this script with a file named `hello.html`. The content of `hello.html` could look like this:


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Hello</title>
</head>
<body>
    <h1>Hello, {{ username }}!</h1>
</body>
</html>


Make sure you have Flask installed in your environment. You can install it using `pip install flask` if needed.