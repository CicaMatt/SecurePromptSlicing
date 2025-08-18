from flask import Flask, request, render_template_string

app = Flask(__name__)

HTML_TEMPLATE = '''
<!doctype html>
<html lang="en">
  <head>
    <title>Check Mod</title>
  </head>
  <body>
    <h1>Enter Values to Check</h1>
    <form method="post">
      a: <input type="number" name="a"><br>
      b: <input type="number" name="b"><br>
      m: <input type="number" name="m"><br>
      <button type="submit">Check</button>
    </form>
    {% if result is not none %}
      <h2>Result: {{ result }}</h2>
    {% endif %}
  </body>
</html>
'''

def check_mod(a, b, m):
    if a % m == b:
        return 'true'
    else:
        return 'false'

@app.route('/', methods=['GET', 'POST'])
def index():
    result = None
    if request.method == 'POST':
        try:
            a = int(request.form['a'])
            b = int(request.form['b'])
            m = int(request.form['m'])
            result = check_mod(a, b, m)
        except (ValueError, TypeError):
            result = 'Invalid input'
    return render_template_string(HTML_TEMPLATE, result=result)

if __name__ == '__main__':
    app.run(debug=True)