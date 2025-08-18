from flask import Flask, render_template_string, request

app = Flask(__name__)

# Dummy credentials for demonstration purposes
USERNAME = "user"
PASSWORD = "pass"

def check_mod():
    username = request.form.get('username')
    password = request.form.get('password')
    
    if username == USERNAME and password == PASSWORD:
        return 'true'
    else:
        return 'false'

@app.route('/', methods=['GET', 'POST'])
def index():
    result = None
    if request.method == 'POST':
        result = check_mod()
        
    html_form = '''
    <!doctype html>
    <title>Login Form</title>
    <h1>Login</h1>
    <form method="post">
      Username: <input type="text" name="username"><br>
      Password: <input type="password" name="password"><br>
      <input type="submit" value="Submit">
    </form>
    '''
    
    if result:
        html_form += f'<h2>Login {"successful" if result == "true" else "failed"}.</h2>'
        
    return render_template_string(html_form)

if __name__ == '__main__':
    app.run(debug=True)