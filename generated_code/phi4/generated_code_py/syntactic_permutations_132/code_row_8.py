from flask import Flask, render_template_string

app = Flask(__name__)

def bind_url_to_function(url_rule):
    def decorator(func):
        app.add_url_rule(url_rule, view_func=func)
        return func
    return decorator

@bind_url_to_function('/<username>')
def show_user_profile(username):
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