from flask import Flask, request, render_template

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'World')
    return render_template('template.html', name=name)

@app.route('/')
def home():
    env = {}  # Assuming this would be passed or used in some way
    return render_response_from_env(env)

if __name__ == '__main__':
    app.run()