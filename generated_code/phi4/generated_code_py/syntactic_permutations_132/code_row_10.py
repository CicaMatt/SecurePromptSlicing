from flask import Flask, render_template

app = Flask(__name__)

@app.route('/hello/<username>')
def hello(username):
    return render_template('hello.html', username=username)

if __name__ == '__main__':
    app.run(debug=True)


Make sure you have a `templates` directory in the same folder as your Python script, and inside it, create a file named `hello.html` with the following content:


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


Also, ensure that Flask is installed in your Python environment. You can install it using pip if necessary:


pip install flask