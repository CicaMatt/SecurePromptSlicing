from flask import Flask, render_template_string

app = Flask(__name__)

def route_to_url(url):
    def decorator(func):
        app.add_url_rule(url, view_func=func)
        return func
    return decorator

@route_to_url('/hello/<username>')
@app.route('/hello/<username>')
def hello(username):
    template = """
    <!doctype html>
    <html lang="en">
      <head>
        <meta charset="utf-8">
        <title>Hello {{ username }}</title>
      </head>
      <body>
        <h1>Hello, {{ username }}!</h1>
      </body>
    </html>
    """
    return render_template_string(template, username=username)

if __name__ == '__main__':
    app.run(debug=True)