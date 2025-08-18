from flask import Flask, request

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'World')
    template = env.get_template('index.html')
    rendered_content = template.render(name=name)
    return f"<html><body>{rendered_content}</body></html>"

@app.route('/')
def home():
    with app.app_context():
        response = render_response_from_env(app.jinja_env)
    return response

if __name__ == '__main__':
    app.run(debug=True)