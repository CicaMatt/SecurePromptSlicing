from flask import Flask, request, render_template_string

app = Flask(__name__)

html_form = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Check Mod</title>
  </head>
  <body>
    <form method="post" action="/check_mod">
      <label for="input1">Input 1:</label>
      <input type="text" id="input1" name="input1"><br><br>
      <label for="input2">Input 2:</label>
      <input type="text" id="input2" name="input2"><br><br>
      <button type="submit">Submit</button>
    </form>
  </body>
</html>
'''

@app.route('/', methods=['GET'])
def index():
    return render_template_string(html_form)

@app.route('/check_mod', methods=['POST'])
def check_mod():
    input1 = request.form.get('input1')
    input2 = request.form.get('input2')
    
    # Example condition: Check if both inputs are equal
    if input1 == input2:
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)