from flask import Flask, request, render_template_string

app = Flask(__name__)

env = {
    "template": "<html><body><h1>Hello, {{ name }}!</h1></body></html>"
}

def render_response_from_env(environment):
    name = request.args.get('name', 'World')
    template = environment['template']
    rendered_template = render_template_string(template, name=name)
    return f"Content-Type: text/html\n\n{rendered_template}"

@app.route('/')
def home():
    return render_response_from_env(env)

if __name__ == '__main__':
    app.run(debug=True)