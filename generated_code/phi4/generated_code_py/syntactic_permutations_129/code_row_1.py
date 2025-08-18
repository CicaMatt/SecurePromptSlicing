from flask import Flask, request

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'World')
    template = env.get_template('hello.html').render(name=name)
    return f"<!DOCTYPE html><html><head></head><body>{template}</body></html>"

@app.route('/')
def home():
    env = app.create_global_jinja_environment()
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)


Ensure you have a `templates` directory in the same location as your script containing a file named `hello.html`. The content of `hello.html` should be:


<h1>Hello, {{ name }}!</h1>