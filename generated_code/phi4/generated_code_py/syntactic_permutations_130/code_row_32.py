from flask import Flask, request, Response

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'World')
    template = env.get_template('greeting.html').render(name=name)
    return Response(template)

@app.route('/')
def home():
    return render_response_from_env(app.jinja_env)

if __name__ == '__main__':
    app.run(debug=True)