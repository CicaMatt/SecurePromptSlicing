from flask import Flask, request

app = Flask(__name__)

def render_response_from_env(env):
    template = env.get('template', 'default_template.html')
    name = request.args.get('name', 'Guest')
    
    # Simulate rendering the template with a placeholder
    rendered_content = f"Hello, {name}! This is from the {template}."

    return f"<html><body>{rendered_content}</body></html>"

@app.route('/')
def home():
    env = {'template': 'home_template.html'}
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)