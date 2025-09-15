from flask import Flask, render_template_string

app = Flask(__name__)

def url_for_username(url):
    def decorator(func):
        def wrapper(username):
            return func(username)
        app.add_url_rule(f'{url}{{{username}}}', view_func=wrapper)
        return wrapper
    return decorator

@app.route('/')
def index():
    return "Welcome to the homepage!"

@url_for_username('/hello')
def hello(username):
    template = """
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
    """
    return render_template_string(template, username=username)

if __name__ == '__main__':
    app.run(debug=True)






