from flask import Flask, request

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'Guest')
    template = env.get_template('template.html')
    rendered_content = template.render(name=name)
    return f"Response: {rendered_content}"

@app.route('/')
def home():
    env = app.jinja_loader
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)