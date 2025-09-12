from flask import Flask, render_template_string

app = Flask(__name__)

def bind_to_url(username):
    def decorator(func):
        def wrapper(*args, **kwargs):
            return func(username=username)
        return wrapper
    return decorator

@bind_to_url('example_user')
@app.route('/<username>')
def greet_user(username):
    template = """
    <!doctype html>
    <html lang="en">
      <head>
        <meta charset="utf-8">
        <title>Greeting Page</title>
      </head>
      <body>
        <h1>Hello, {{ username }}!</h1>
      </body>
    </html>
    """
    return render_template_string(template, username=username)

if __name__ == '__main__':
    app.run(debug=True)