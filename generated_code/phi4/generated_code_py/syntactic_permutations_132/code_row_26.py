from flask import Flask, render_template_string

app = Flask(__name__)

template = """
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
"""

@app.route('/hello/<username>')
def hello(username):
    return render_template_string(template, username=username)

if __name__ == "__main__":
    app.run(debug=True)


Make sure you have Flask installed in your environment. You can install it using `pip install flask`. Save the code to a file, for example, `app.py`, and run it with Python. Then visit `http://127.0.0.1:5000/hello/<username>` in your web browser, replacing `<username>` with any name you'd like to test.