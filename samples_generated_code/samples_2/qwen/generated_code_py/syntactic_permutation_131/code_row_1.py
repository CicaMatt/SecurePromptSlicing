from flask import Flask, request, render_template_string

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'World')
    template = env.get_template('hello.html')
    rendered_template = template.render(name=name)
    return rendered_template

@app.route('/')
def home():
    from jinja2 import Environment, select_autoescape
    file_loader = FileSystemLoader('templates')
    env = Environment(loader=file_loader, autoescape=select_autoescape())
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)



<!-- templates/hello.html -->
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