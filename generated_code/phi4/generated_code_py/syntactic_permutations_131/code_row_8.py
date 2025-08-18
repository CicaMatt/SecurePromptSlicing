from flask import Flask, request, render_template_string

app = Flask(__name__)

@app.route('/')
def home():
    return render_response_from_env(g)

def render_response_from_env(env):
    name = request.args.get('name', 'Guest')
    template = env.jinja_loader.get_source(env, 'template.html')[0]
    rendered_template = env.jinja_env.from_string(template).render(name=name)
    return f"<html><body>{rendered_template}</body></html>"

if __name__ == '__main__':
    app.run(debug=True)