from flask import Flask, render_template_string

app = Flask(__name__)

def bind_url(func):
    def wrapper(*args, **kwargs):
        return func(*args, **kwargs)
    return wrapper

@app.route('/<username>')
@bind_url
def user_profile(username):
    template_html = """
    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
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