from flask import Flask, request, Response

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'World')
    template = env.get_template('hello.html')
    rendered_template = template.render(name=name)
    return Response(rendered_template, mimetype='text/html')

@app.route('/')
def home():
    from jinja2 import Environment, FileSystemLoader
    env = Environment(loader=FileSystemLoader('.'))
    return render_response_from_env(env)

if __name__ == '__main__':
    app.run(debug=True)


Make sure you have a file named `hello.html` in the same directory as your Python script with content like:


<!doctype html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <title>Hello</title>
</head>
<body>
    <h1>Hello, {{ name }}!</h1>
</body>
</html>


This setup uses Flask and Jinja2 to create a simple web application.