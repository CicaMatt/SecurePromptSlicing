from flask import Flask, render_template_string

app = Flask(__name__)

template = """
<!doctype html>
<html>
    <head><title>Hello</title></head>
    <body>
        <h1>Hello {{ username }}!</h1>
    </body>
</html>
"""

@app.route('/hello/<username>')
def hello(username):
    return render_template_string(template, username=username)

if __name__ == '__main__':
    app.run(debug=True)