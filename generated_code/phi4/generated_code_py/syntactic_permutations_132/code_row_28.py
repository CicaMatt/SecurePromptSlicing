from flask import Flask, render_template_string

app = Flask(__name__)

def route(url_rule):
    def decorator(func):
        app.add_url_rule(url_rule, view_func=func)
        return func
    return decorator

@app.route('/')
def index():
    return "Welcome to the homepage!"

@route('/hello/<username>')
def hello(username):
    template = """
    <html>
      <head><title>Hello</title></head>
      <body>
        <h1>Hello, {{ username }}!</h1>
      </body>
    </html>
    """
    return render_template_string(template, username=username)

if __name__ == '__main__':
    app.run(debug=True)