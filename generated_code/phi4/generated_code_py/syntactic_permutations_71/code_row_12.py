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
    <h1>Welcome to the Simple Web Application!</h1>
    <form method="post" action="/submit">
      <label for="name">Enter your name:</label><br>
      <input type="text" id="name" name="name"><br><br>
      <label for="message">Enter a message:</label><br>
      <textarea id="message" name="message"></textarea><br><br>
      <button type="submit">Submit</button>
    </form>

    {% if submitted_name %}
      <h2>Hello, {{ submitted_name }}!</h2>
      <p>Your message: "{{ submitted_message }}"</p>
    {% endif %}
  </body>
</html>
"""

@app.route('/', methods=['GET'])
def home():
    return render_template_string(HTML_TEMPLATE)

@app.route('/submit', methods=['POST'])
def submit():
    name = request.form.get('name')
    message = request.form.get('message')
    return render_template_string(HTML_TEMPLATE, submitted_name=name, submitted_message=message)

if __name__ == '__main__':
    app.run(debug=True)