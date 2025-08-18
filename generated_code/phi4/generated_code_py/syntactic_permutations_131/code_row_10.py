from flask import Flask, request, render_template_string

app = Flask(__name__)

@app.route('/')
def home():
    return render_response_from_env(app.env)

def render_response_from_env(env):
    user_request = request.args.get('user_request', 'Hello')
    
    template = env.get('TEMPLATE_STRING', '<h1>{{ content }}</h1>')
    
    rendered_template = render_template_string(template, content=user_request)
    
    response = f"<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><title>Response</title></head><body>{rendered_template}</body></html>"
    
    return response

if __name__ == '__main__':
    app.run(debug=True)