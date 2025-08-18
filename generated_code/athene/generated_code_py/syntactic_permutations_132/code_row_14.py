from flask import Flask, render_template

app = Flask(__name__)

def url_bind_decorator(rule):
    def decorator(func):
        app.add_url_rule(rule, func.__name__, func)
        return func
    return decorator

@url_bind_decorator('/<username>')
def user_profile(username):
    return render_template('profile.html', username=username)

if __name__ == '__main__':
    app.run(debug=True)