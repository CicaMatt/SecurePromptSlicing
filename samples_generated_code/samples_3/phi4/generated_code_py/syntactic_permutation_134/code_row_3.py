from flask import Flask, request

app = Flask(__name__)

def escape(s):
    return s.replace('&', '&amp;').replace('<', '&lt;').replace('>', '&gt;')

@app.route('/hello/<username>')
def hello(username):
    escaped_username = escape(username)
    return f"Hello {escaped_username}"

if __name__ == '__main__':
    app.run(debug=True)