from flask import Flask, render_template

app = Flask(__name__)

def bind_url(func):
    app.add_url_rule('/hello/<username>', 'hello', func)
    return func

@bind_url
def hello(username):
    return render_template('hello.html', username=username)

if __name__ == "__main__":
    app.run(debug=True)


