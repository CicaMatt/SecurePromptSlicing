from flask import Flask, render_template

app = Flask(__name__)

@app.route('/hello/<username>')
def hello(username):
    return render_template('hello.html', username=username)

if __name__ == '__main__':
    app.run(debug=True)


To run this code:

1. Ensure you have Flask installed: `pip install flask`
2. Create a directory called `templates` in the same location as your script.
3. Inside the `templates` directory, create a file named `hello.html` with the following content:


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


4. Run your Python script using `python script_name.py`.