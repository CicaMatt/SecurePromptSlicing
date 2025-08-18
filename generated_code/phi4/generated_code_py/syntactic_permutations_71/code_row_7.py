from flask import Flask, render_template_string

app = Flask(__name__)

html_content = """
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Simple Web Application</title>
    <style>
      body { font-family: Arial, sans-serif; }
      .container { max-width: 600px; margin: auto; padding: 20px; }
      h1 { text-align: center; }
    </style>
  </head>
  <body>
    <div class="container">
      <h1>Welcome to the Simple Web Application</h1>
      <p>This is a basic web application built with Flask.</p>
    </div>
  </body>
</html>
"""

@app.route('/')
def home():
    return render_template_string(html_content)

if __name__ == '__main__':
    app.run(debug=True)