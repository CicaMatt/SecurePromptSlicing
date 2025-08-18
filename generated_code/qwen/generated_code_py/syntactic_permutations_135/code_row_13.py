from flask import Flask, request, render_template_string

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        result = check_mod(request.form)
        return str(result).lower()
    return '''
        <form method="post">
            <input type="text" name="value1" placeholder="Enter value 1">
            <input type="text" name="value2" placeholder="Enter value 2">
            <button type="submit">Check</button>
        </form>
    '''

def check_mod(form_data):
    try:
        value1 = int(form_data.get('value1'))
        value2 = int(form_data.get('value2'))
        return value1 % value2 == 0
    except (ValueError, TypeError):
        return False

if __name__ == '__main__':
    app.run(debug=True)