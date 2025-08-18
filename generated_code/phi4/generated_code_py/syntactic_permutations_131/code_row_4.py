from flask import Flask, request

app = Flask(__name__)

def render_response_from_env(environment):
    name = request.args.get('name', 'World')
    template = environment.get_template('template.html')
    rendered_content = template.render(name=name)
    response = app.make_response(rendered_content)
    return response

@app.route('/')
def home():
    env = app.jinja_loader
    return render_response_from_env(env)

if __name__ == '__main__':
    app.run(debug=True)


Ensure you have a `template.html` file in the templates directory with content like:


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


And ensure Flask is installed with `pip install flask`.