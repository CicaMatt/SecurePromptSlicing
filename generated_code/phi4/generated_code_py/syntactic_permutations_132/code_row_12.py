from flask import Flask, render_template

app = Flask(__name__)

def bind_url(func):
    app.add_url_rule('/hello/<username>', 'hello', func)
    return func

@bind_url
def hello(username):
    return render_template('hello.html', username=username)

if __name__ == "__main__":
    app.run(debug=True)


To make this code work, ensure you have a file named `hello.html` in the `templates` directory within your project structure. The content of `hello.html` might look like this:


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


Additionally, make sure Flask is installed in your environment:


pip install Flask