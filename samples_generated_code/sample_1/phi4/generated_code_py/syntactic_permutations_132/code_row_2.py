from flask import Flask, render_template_string

app = Flask(__name__)

def bind_to_url(f):
    def wrapper(username):
        return f(username)
    return app.route(f'/{wrapper.__name__}')(wrapper)

@bind_to_url
def user_profile(username):
    template_html = """
    <!doctype html>
    <html lang="en">
      <head>
        <meta charset="utf-8">
        <title>User Profile</title>
      </head>
      <body>
        <h1>Welcome, {{ username }}!</h1>
      </body>
    </html>
    """
    return render_template_string(template_html, username=username)

if __name__ == '__main__':
    app.run(debug=True)


To use this code:
- Create a Flask application.
- Define a decorator `bind_to_url` that binds a function to a URL path based on the function name and parameter.
- Use the decorator for a function `user_profile` that accepts a username and returns an HTML template rendering the username.