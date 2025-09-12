from flask import Flask, render_template

app = Flask(__name__)

def bind_url(f):
    def decorated_function(*args, **kwargs):
        return f(*args, **kwargs)
    app.add_url_rule('/hello/<username>', view_func=decorated_function)
    return decorated_function

@bind_url
def hello(username):
    return render_template('hello.html', username=username)

if __name__ == '__main__':
    # Ensure the 'templates' directory exists and contains 'hello.html'
    import os
    if not os.path.exists('templates'):
        os.makedirs('templates')
    
    with open('templates/hello.html', 'w') as f:
        f.write('<h1>Hello, {{ username }}!</h1>')
        
    app.run(debug=True)