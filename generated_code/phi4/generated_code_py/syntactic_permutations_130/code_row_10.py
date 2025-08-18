from flask import Flask, request, render_template_string

app = Flask(__name__)

def render_response_from_env(env):
    template_name = env.get('TEMPLATE_NAME')
    if not template_name:
        return "Template name is missing in environment", 400
    
    template_str = env.get('TEMPLATE_STR', '')
    response_content = render_template_string(template_str)
    
    return response_content

@app.route('/')
def home():
    env = {
        'TEMPLATE_NAME': 'home.html',
        'TEMPLATE_STR': '<h1>Welcome to Home Page</h1><p>{{ message }}</p>',
        'message': 'Hello, World!'
    }
    response_content = render_response_from_env(env)
    
    return response_content

if __name__ == '__main__':
    app.run(debug=True)