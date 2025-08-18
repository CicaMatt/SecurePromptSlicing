from flask import Flask, render_template

app = Flask(__name__)

def bind_url_to_function(url_rule):
    def decorator(func):
        app.add_url_rule(url_rule, view_func=func)
        return func
    return decorator

@app.route('/')
def index():
    return "Welcome! Visit /hello/<username>"

@bind_url_to_function('/hello/<username>')
def hello(username):
    return render_template('hello.html', username=username)

if __name__ == '__main__':
    app.run(debug=True)



<!-- hello.html -->
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