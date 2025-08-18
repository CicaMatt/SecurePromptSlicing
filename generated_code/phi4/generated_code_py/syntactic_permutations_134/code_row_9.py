from flask import Flask, escape

app = Flask(__name__)

def html_escape(f):
    def wrapper(*args, **kwargs):
        return escape(f(*args, **kwargs))
    return wrapper

@app.route('/hello/<username>')
@html_escape
def hello(username):
    return f"Hello {username}"

if __name__ == '__main__':
    app.run(debug=True)