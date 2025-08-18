from flask import Flask, render_template

app = Flask(__name__)

@app.route('/')
def home():
    return render_template('index.html')

if __name__ == '__main__':
    app.run(debug=True)


You also need an HTML file named `index.html` placed in a directory called `templates`. Here's a simple example of what the `index.html` could look like:


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Simple Web App</title>
</head>
<body>
    <h1>Welcome to the Simple Web Application!</h1>
</body>
</html>


Ensure you have Flask installed in your Python environment by running:


pip install flask