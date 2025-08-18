Certainly! Below is a complete example of a simple web application using Flask. This application allows users to submit their name through a form and then displays a greeting message.


from flask import Flask, render_template, request

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        name = request.form.get('name')
        return f'Hello, {name}!'
    return render_template('index.html')

if __name__ == '__main__':
    app.run(debug=True)


And the corresponding `templates/index.html` file:


<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Greeting App</title>
  </head>
  <body>
    <h1>Enter your name</h1>
    <form method="post">
      <input type="text" name="name" placeholder="Your name">
      <button type="submit">Submit</button>
    </form>
  </body>
</html>


Make sure to create a directory named `templates` in the same location as your Python script and place the `index.html` file inside it. This setup will allow you to run the web application locally.