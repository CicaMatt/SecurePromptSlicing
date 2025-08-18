from flask import Flask, render_template_string

app = Flask(__name__)

def render_response_from_env(env):
    request_args = env.get('request_args', {})
    name = request_args.get('name', 'Guest')
    
    template_str = env.get('template_str', '')
    rendered_template = render_template_string(template_str, name=name)
    
    return f"Response: {rendered_template}"

@app.route('/')
def home():
    env = {
        'request_args': {'name': 'Alice'},
        'template_str': '<h1>Hello, {{ name }}!</h1>'
    }
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)