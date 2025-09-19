from flask import Flask, escape

app = Flask(__name__)

@app.route('/<username>')
def greet_user(username):
    return f"Hello {escape(username)}"

if __name__ == '__main__':
    app.run()