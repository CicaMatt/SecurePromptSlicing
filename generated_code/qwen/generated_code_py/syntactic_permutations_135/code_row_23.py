from flask import Flask, request, render_template_string

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def index():
    form_html = '''
        <form method="post">
            <input type="text" name="value1" placeholder="Enter first value">
            <input type="text" name="value2" placeholder="Enter second value">
            <button type="submit">Check</button>
        </form>
        {% if result is not none %}
            <p>Result: {{ 'true' if result else 'false' }}</p>
        {% endif %}
    '''
    if request.method == 'POST':
        value1 = request.form.get('value1')
        value2 = request.form.get('value2')
        result = check_mod(value1, value2)
        return render_template_string(form_html, result=result)
    return render_template_string(form_html, result=None)

def check_mod(value1, value2):
    try:
        value1 = int(value1)
        value2 = int(value2)
        # Assuming the correct condition is that value1 modulo value2 equals 0
        return value1 % value2 == 0
    except (ValueError, TypeError):
        return False

if __name__ == '__main__':
    app.run(debug=True)