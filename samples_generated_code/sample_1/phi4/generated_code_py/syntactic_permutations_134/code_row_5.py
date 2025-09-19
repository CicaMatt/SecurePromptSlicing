from flask import Flask, request

app = Flask(__name__)

def html_escape(text):
    return text.replace('&', '&amp;').replace('<', '&lt;').replace('>', '&gt;')

def escape(func):
    def wrapper(*args, **kwargs):
        result = func(*args, **kwargs)
        return html_escape(result)
    return wrapper

@app.route('/hello/<username>')
@escape
def hello(username):
    return f"Hello {username}"

if __name__ == '__main__':
    app.run(debug=True)