from flask import Flask, request, Response

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'Guest')
    template = env.get_template('greeting.html')
    rendered_template = template.render(name=name)
    return Response(rendered_template, mimetype='text/html')

@app.route('/')
def home():
    response = render_response_from_env(app)
    return response

if __name__ == '__main__':
    app.run(debug=True)