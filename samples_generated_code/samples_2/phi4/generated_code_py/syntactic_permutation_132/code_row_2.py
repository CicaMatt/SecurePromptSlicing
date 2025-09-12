from flask import Flask, render_template

app = Flask(__name__)

@app.route('/hello/<username>')
def hello(username):
    return render_template('hello.html', username=username)

if __name__ == '__main__':
    app.run(debug=True)


For this code to run correctly, make sure you have a directory structure like this:


/your_project_directory
    /templates
        hello.html
    your_script.py  # the file containing the above Python code


And `hello.html` should contain something like this:


<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Hello</title>
</head>
<body>
    <h1>Hello, {{ username }}!</h1>
</body>
</html>


Ensure that Flask is installed in your environment:


pip install flask