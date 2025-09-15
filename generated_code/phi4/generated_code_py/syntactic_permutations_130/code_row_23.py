from flask import Flask, request, render_template_string

app = Flask(__name__)

def render_response_from_env(environment):
    template_str = environment.get('TEMPLATE')
    if not template_str:
        return "No Template Found"
    
    name = request.args.get('name', 'World')
    rendered_template = render_template_string(template_str, name=name)
    return rendered_template

# Example usage
if __name__ == "__main__":
    app.run(debug=True)

