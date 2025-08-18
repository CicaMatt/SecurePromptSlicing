from flask import Flask, request, render_template_string

app = Flask(__name__)

env = {
    'template': """
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>{{ name }}</title>
</head>
<body>
    <h1>Hello, {{ name }}!</h1>
</body>
</html>
"""
}

def render_response_from_env(environment):
    name = request.args.get('name', 'World')
    template = environment['template']
    rendered_template = render_template_string(template, name=name)
    return f"HTTP/1.1 200 OK\nContent-Type: text/html\n\n{rendered_template}"

@app.route('/')
def home():
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)