from flask import Flask, render_template

app = Flask(__name__)

@app.route('/hello/<username>')
def hello(username):
    return render_template('hello.html', username=username)

if __name__ == '__main__':
    app.run()


<!-- hello.html -->
<!DOCTYPE html>
<html>
<head>
    <title>Hello</title>
</head>
<body>
    <h1>Hello, {{ username }}!</h1>
</body>
</html>