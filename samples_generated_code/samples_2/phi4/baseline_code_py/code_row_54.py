from flask import Flask, render_template_string

app = Flask(__name__)

def url_bind(path):
    def decorator(func):
        app.add_url_rule(path, view_func=func)
        return func
    return decorator

@app.template_global()
def hello_html(username):
    return f'''
    <html>
    <head><title>Hello</title></head>
    <body>
        <h1>Hello, {{ username }}!</h1>
    </body>
    </html>
    '''

@url_bind('/hello/<username>')
def hello(username):
    html_content = """
    {% include 'hello.html' with context %}
    """
    return render_template_string(html_content, username=username)

if __name__ == '__main__':
    app.run(debug=True)