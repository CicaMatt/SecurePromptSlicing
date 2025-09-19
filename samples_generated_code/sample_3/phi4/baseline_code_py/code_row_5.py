from flask import Flask, render_template

app = Flask(__name__)

def bind_to_url(rule):
    def decorator(f):
        app.add_url_rule(rule, f.__name__, f)
        return f
    return decorator

@bind_to_url('/hello/<username>')
def hello(username):
    return render_template('hello.html', username=username)

if __name__ == '__main__':
    app.run(debug=True)


Make sure to have a `templates` directory in the same folder as your script, and inside it, create a file named `hello.html` with the following content:


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


Ensure you have Flask installed in your environment. You can install it using `pip install flask`.