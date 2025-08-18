from flask import Flask, render_template_string

app = Flask(__name__)

def bind_url(func):
    app.add_url_rule('/hello/<username>', 'hello', func)
    return func

@bind_url
def hello(username):
    template = '''
    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Hello</title>
    </head>
    <body>
        <h1>Hello, {{ username }}!</h1>
    </body>
    </html>
    '''
    return render_template_string(template, username=username)

if __name__ == '__main__':
    app.run(debug=True)