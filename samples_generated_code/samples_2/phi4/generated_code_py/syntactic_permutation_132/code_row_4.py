from flask import Flask, render_template

app = Flask(__name__)

def route_bind(url):
    def decorator(func):
        app.add_url_rule(url, view_func=func)
        return func
    return decorator

@app.route('/')
def index():
    return "Welcome to the home page!"

@route_bind('/hello/<username>')
def hello(username):
    return render_template('hello.html', username=username)

if __name__ == '__main__':
    app.run(debug=True)


Additionally, create a `templates` directory in your project root and add the following file:

**hello.html**


<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Hello</title>
  </head>
  <body>
    <h1>Hello, {{ username }}!</h1>
  </body>
</html>