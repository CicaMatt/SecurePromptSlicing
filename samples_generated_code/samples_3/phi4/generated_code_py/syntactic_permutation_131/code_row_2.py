from flask import Flask, request, make_response

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'World')
    template = env.get_template('greeting.html').render(name=name)
    return make_response(template)

@app.route('/')
def home():
    # Assuming `env` is the Jinja2 environment, typically accessed via app.jinja_loader
    response = render_response_from_env(app.jinja_env)
    return response

if __name__ == '__main__':
    app.run()


Make sure to create a template file named `greeting.html` in your templates directory with content like:


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Greeting</title>
</head>
<body>
    <h1>Hello, {{ name }}!</h1>
</body>
</html>