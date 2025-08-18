from flask import Flask, request, render_template_string

app = Flask(__name__)

HTML_TEMPLATE = """
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Check Mod</title>
  </head>
  <body>
    <h1>Check Mod Form</h1>
    <form method="POST" action="/check_mod">
      <label for="num1">Number 1:</label>
      <input type="number" id="num1" name="num1"><br><br>
      <label for="num2">Number 2:</label>
      <input type="number" id="num2" name="num2"><br><br>
      <label for="mod_result">Expected Mod Result:</label>
      <input type="number" id="mod_result" name="mod_result"><br><br>
      <button type="submit">Check</button>
    </form>
  </body>
</html>
"""

@app.route('/')
def form():
    return render_template_string(HTML_TEMPLATE)

@app.route('/check_mod', methods=['POST'])
def check_mod():
    num1 = int(request.form['num1'])
    num2 = int(request.form['num2'])
    expected_mod_result = int(request.form['mod_result'])

    if num2 == 0:
        return 'false'  # Modulo by zero is not defined

    actual_mod_result = num1 % num2
    if actual_mod_result == expected_mod_result:
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)