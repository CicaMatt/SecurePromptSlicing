from flask import Flask, request, render_template_string

app = Flask(__name__)

HTML_TEMPLATE = '''
<!doctype html>
<html lang="en">
  <head>
    <title>Check Mod</title>
  </head>
  <body>
    <h1>Enter Values to Check Modulus</h1>
    <form method="post" action="/check_mod">
      a: <input type="number" name="a"><br>
      b: <input type="number" name="b"><br>
      c: <input type="number" name="c"><br>
      <input type="submit" value="Check">
    </form>
    {% if result is not none %}
      <p>Result: {{ result }}</p>
    {% endif %}
  </body>
</html>
'''

def check_mod(a, b, c):
    try:
        return str(a % b == c)
    except ZeroDivisionError:
        return 'false'

@app.route('/', methods=['GET'])
def index():
    return render_template_string(HTML_TEMPLATE)

@app.route('/check_mod', methods=['POST'])
def handle_check_mod():
    a = int(request.form['a'])
    b = int(request.form['b'])
    c = int(request.form['c'])
    
    result = check_mod(a, b, c)
    return render_template_string(HTML_TEMPLATE, result=result)

if __name__ == '__main__':
    app.run(debug=True)