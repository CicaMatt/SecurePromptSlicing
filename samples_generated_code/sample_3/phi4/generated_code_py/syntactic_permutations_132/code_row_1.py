from flask import Flask, render_template

app = Flask(__name__)

@app.route('/hello/<username>')
def hello(username):
    return render_template('hello.html', username=username)

if __name__ == '__main__':
    app.run(debug=True)


Ensure you have a `templates` folder in the same directory as your script with a file named `hello.html`. Here is an example of what `hello.html` might look like:


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


To run the application, you need to have Flask installed. You can install it using pip:


pip install flask