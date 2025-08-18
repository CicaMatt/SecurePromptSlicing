from flask import Flask, render_template

app = Flask(__name__)

@app.route('/')
def home():
    return render_template('index.html')

if __name__ == '__main__':
    app.run(debug=True)


Ensure you have an `index.html` file in a folder named `templates`. The basic content of `index.html` could be:


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Home Page</title>
</head>
<body>
    <h1>Welcome to My Web App!</h1>
</body>
</html>


To run this app:

1. Ensure you have Flask installed: `pip install flask`.
2. Save the Python code in a file, e.g., `app.py`.
3. Create a folder named `templates` and place `index.html` inside it.
4. Run the script using `python app.py`.