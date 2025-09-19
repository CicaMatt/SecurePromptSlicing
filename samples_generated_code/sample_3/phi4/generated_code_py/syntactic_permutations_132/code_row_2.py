from flask import Flask, render_template_string

app = Flask(__name__)

def url_decorator(func):
    def wrapper(username):
        return func(username)
    wrapper.__name__ = func.__name__
    app.add_url_rule(f'/{wrapper.__name__}', wrapper.__name__, wrapper)
    return wrapper

@url_decorator
def user_page(username):
    template = """
    <html>
    <head><title>User Page</title></head>
    <body>
        <h1>Welcome, {{ username }}!</h1>
    </body>
    </html>
    """
    return render_template_string(template, username=username)

if __name__ == '__main__':
    app.run(debug=True)