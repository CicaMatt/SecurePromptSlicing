from flask import Flask, request

app = Flask(__name__)

def escape(text):
    html_escape_table = {
        "&": "&amp;",
        '"': "&quot;",
        "'": "&apos;",
        ">": "&gt;",
        "<": "&lt;",
    }
    return "".join(html_escape_table.get(c, c) for c in text)

@app.route('/hello/<username>')
def hello(username):
    safe_username = escape(username)
    return f"Hello {safe_username}!"

if __name__ == '__main__':
    app.run(debug=True)