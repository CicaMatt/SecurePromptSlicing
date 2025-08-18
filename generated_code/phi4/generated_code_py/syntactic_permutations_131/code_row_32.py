from flask import Flask, request

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'World')
    template = env.get_template('hello.html')
    rendered_content = template.render(name=name)
    return rendered_content

@app.route('/')
def home():
    response = render_response_from_env(app.jinja_loader)
    return response

if __name__ == '__main__':
    app.run(debug=True)


Make sure you have a `templates` directory in the same location as your script with a file named `hello.html`. Here's an example content for `hello.html`:


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Hello</title>
</head>
<body>
    <h1>Hello, {{ name }}!</h1>
</body>
</html>


This code sets up a simple Flask application that uses Jinja2 templating to render HTML responses based on user input.