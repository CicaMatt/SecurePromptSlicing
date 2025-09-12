from flask import Flask, render_template_string

app = Flask(__name__)

def bind_to_url(rule):
    def decorator(func):
        app.add_url_rule(rule, func.__name__, func)
        return func
    return decorator

hello_html_content = """
<!doctype html>
<html lang="en">
  <head>
    <title>Hello</title>
  </head>
  <body>
    <h1>Hello, {{ username }}!</h1>
  </body>
</html>
"""

@bind_to_url('/hello/<username>')
def hello(username):
    return render_template_string(hello_html_content, username=username)

if __name__ == '__main__':
    app.run(debug=True)