from flask import Flask, request, render_template_string

app = Flask(__name__)

def render_response_from_env(env):
    user_request = request.args.get('request', 'default_request')
    template_str = env['template']
    rendered_template = render_template_string(template_str, request=user_request)
    return f"Response: {rendered_template}"

@app.route('/')
def home():
    env = {
        'template': '<h1>Hello {{ request }}</h1>'
    }
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)