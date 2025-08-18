from flask import Flask, request, render_template_string

app = Flask(__name__)

HTML_TEMPLATE = """
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Simple Web App</title>
  </head>
  <body>
    <h1>Welcome to the Simple Web App</h1>
    <form method="post">
      <label for="name">Enter your name:</label>
      <input type="text" id="name" name="name" required>
      <button type="submit">Submit</button>
    </form>
    {% if name %}
      <p>Hello, {{ name }}!</p>
    {% endif %}
  </body>
</html>
"""

@app.route('/', methods=['GET', 'POST'])
def index():
    name = None
    if request.method == 'POST':
        name = request.form.get('name')
    return render_template_string(HTML_TEMPLATE, name=name)

if __name__ == '__main__':
    app.run(debug=True)