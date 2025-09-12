from flask import Flask, request, render_template_string

app = Flask(__name__)

env = {
    "template1": "<html><body><h1>{{ title }}</h1></body></html>",
}

def render_response_from_env(env):
    template_name = request.args.get('name')
    if template_name in env:
        template_str = env[template_name]
        return render_template_string(template_str, title="Hello from Template!")
    else:
        return "Template not found", 404

@app.route('/')
def home():
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)