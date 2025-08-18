from flask import Flask, render_template_string

app = Flask(__name__)

def bind_url(f):
    def wrapper(*args, **kwargs):
        return f(*args, **kwargs)
    return wrapper

@app.route('/hello/<username>')
@bind_url
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