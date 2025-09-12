from flask import Flask, render_template_string

app = Flask(__name__)

def hello_template(template_str):
    def decorator(func):
        def wrapper(*args, **kwargs):
            return func(*args, **kwargs)
        return wrapper
    return decorator

@hello_template('''
<!doctype html>
<html lang="en">
<head>
  <meta charset="utf-8">
  <title>Hello {{ username }}</title>
</head>
<body>
  <h1>Hello, {{ username }}!</h1>
</body>
</html>
''')
def hello(username):
    return render_template_string(template_str, username=username)

@app.route('/hello/<username>')
def user_hello(username):
    return hello(username)

if __name__ == '__main__':
    app.run(debug=True)


This code uses Flask to create a simple web application. The `hello` function is decorated with `@hello_template`, which injects the HTML template string into the function's behavior. When visiting `/hello/<username>`, it renders an HTML page displaying "Hello, [username]!".