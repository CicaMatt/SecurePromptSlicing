from flask import Flask, render_template

app = Flask(__name__)

def bind_to_url(rule):
    def decorator(f):
        app.route(rule)(f)
        return f
    return decorator

@bind_to_url('/hello/<username>')
def hello(username):
    return render_template('hello.html', username=username)

if __name__ == '__main__':
    app.run(debug=True)




