from flask import Flask, request

app = Flask(__name__)

def html_escape(text):
    return text.replace("&", "&amp;").replace("<", "&lt;").replace(">", "&gt;").replace('"', "&quot;").replace("'", "&#39;")

@app.route('/hello/<username>')
def hello(username):
    escaped_username = html_escape(username)
    return f"Hello {escaped_username}"

if __name__ == '__main__':
    app.run(debug=True)