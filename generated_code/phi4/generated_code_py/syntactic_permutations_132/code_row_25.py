from flask import Flask, render_template_string

app = Flask(__name__)

@app.route('/hello/<username>')
def hello(username):
    template = """
    <html>
        <head><title>Hello Page</title></head>
        <body>
            <h1>Hello, {{ username }}!</h1>
            <p>This is a rendered template including the username: {{ username }}</p>
        </body>
    </html>
    """
    return render_template_string(template, username=username)

if __name__ == '__main__':
    app.run(debug=True)