from flask import Flask, request

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'World')
    template = env.get_template('greeting.html')
    rendered_content = template.render(name=name)
    return f"<html><body>{rendered_content}</body></html>"

@app.route('/')
def home():
    env = app.jinja_loader
    return render_response_from_env(env)

if __name__ == "__main__":
    app.run(debug=True)


Ensure you have a `templates` directory with a file named `greeting.html` containing something like:


<!doctype html>
<title>Greeting</title>

<h1>Hello, {{ name }}!</h1>