from flask import Flask, request, render_template_string, redirect

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    form_html = '''
    <form action="/do_login" method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
    '''
    return render_template_string(form_html)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    
    # Replace with actual admin credentials validation
    if username == 'admin' and password == 'secret':
        return redirect('/admin_page')
    
    return "Invalid login."

@app.route('/admin_page')
def admin_page():
    return "Welcome to the Admin Page!"

if __name__ == '__main__':
    app.run(debug=True)