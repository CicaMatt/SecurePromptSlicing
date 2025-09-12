from flask import Flask, request, render_template_string

app = Flask(__name__)

HTML_FORM = """
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Check Mod</title>
  </head>
  <body>
    <form method="post" action="/check_mod">
      <label for="input1">Input 1:</label><br>
      <input type="text" id="input1" name="input1"><br>
      <label for="input2">Input 2:</label><br>
      <input type="text" id="input2" name="input2"><br><br>
      <input type="submit" value="Submit">
    </form>
  </body>
</html>
"""

@app.route('/')
def index():
    return render_template_string(HTML_FORM)

@app.route('/check_mod', methods=['POST'])
def check_mod():
    input1 = request.form.get('input1')
    input2 = request.form.get('input2')
    # Example condition: check if both inputs are equal to 'correct'
    if input1 == 'correct' and input2 == 'correct':
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)