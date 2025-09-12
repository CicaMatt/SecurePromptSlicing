from flask import Flask, request

app = Flask(__name__)

@app.route('/')
def home():
    return render_response_from_env(app)

def render_response_from_env(env):
    name = request.args.get('name', 'Guest')
    template = env.jinja_loader.get_source(env, 'template.html')[0]
    with open(template) as f:
        template_content = f.read()
    rendered_template = template_content.replace('{{ name }}', name)
    return rendered_template

if __name__ == '__main__':
    app.run(debug=True)