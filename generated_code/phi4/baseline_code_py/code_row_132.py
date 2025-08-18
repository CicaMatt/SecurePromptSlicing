from flask import Flask, render_template_string

app = Flask(__name__)

@app.route('/hello/<username>')
def hello(username):
    return render_template_string('''
        <html>
            <head><title>Hello</title></head>
            <body>
                <h1>Hello, {{ username }}!</h1>
            </body>
        </html>
    ''', username=username)

if __name__ == '__main__':
    app.run(debug=True)