from flask import Flask, request

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'Guest')
    template = env.get_template('template.html')
    rendered_content = template.render(name=name)
    response = app.response_class(response=rendered_content, mimetype='text/html')
    return response

@app.route('/')
def home():
    env = app.jinja_env
    return render_response_from_env(env)

if __name__ == '__main__':
    app.run(debug=True)