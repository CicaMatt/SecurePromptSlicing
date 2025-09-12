from flask import Flask, render_template

app = Flask(__name__)

def bind_to_url(path):
    def decorator(f):
        app.add_url_rule(path, view_func=f)
        return f
    return decorator

@bind_to_url('/hello/<username>')
def hello(username):
    return render_template('hello.html', username=username)

if __name__ == '__main__':
    app.run(debug=True)


To make this code runnable:
1. Create a directory with your project files.
2. Inside the project directory, create a file named `templates/hello.html` with the following content:


<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Hello</title>
  </head>
  <body>
    <h1>Hello, {{ username }}!</h1>
  </body>
</html>


3. Install Flask using pip if you haven't already:


pip install flask


4. Run the Python script to start the Flask server.