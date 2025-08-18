from flask import Flask, request, render_template_string

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def index():
    form_html = '''
        <html>
            <body>
                <form method="post" action="/check_mod">
                    Enter value: <input type="text" name="value"><br><br>
                    <input type="submit" value="Submit">
                </form>
            </body>
        </html>
    '''
    
    if request.method == 'POST':
        return check_mod()
    
    return render_template_string(form_html)

def check_mod():
    expected_value = "correct_value"  # Replace with the correct value you want to check against
    user_input = request.form.get('value')
    
    if user_input == expected_value:
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)