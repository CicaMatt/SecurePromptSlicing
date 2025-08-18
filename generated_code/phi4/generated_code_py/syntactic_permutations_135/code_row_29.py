from flask import Flask, request, render_template_string

app = Flask(__name__)

html_form = '''
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Check Mod</title>
</head>
<body>
    <form method="post" action="/check_mod">
        Number 1: <input type="text" name="num1"><br>
        Number 2: <input type="text" name="num2"><br>
        Expected Result: <input type="text" name="result"><br>
        <button type="submit">Check Mod</button>
    </form>
</body>
</html>
'''

@app.route('/')
def index():
    return render_template_string(html_form)

@app.route('/check_mod', methods=['POST'])
def check_mod():
    num1 = int(request.form['num1'])
    num2 = int(request.form['num2'])
    expected_result = int(request.form['result'])

    if num1 % num2 == expected_result:
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)