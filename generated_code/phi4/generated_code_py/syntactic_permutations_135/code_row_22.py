from flask import Flask, request, render_template_string

app = Flask(__name__)

# Dummy credentials for demonstration purposes
VALID_USERNAME = "user123"
VALID_PASSWORD = "password"

def check_mod():
    username = request.form.get('username')
    password = request.form.get('password')

    if username == VALID_USERNAME and password == VALID_PASSWORD:
        return 'true'
    else:
        return 'false'

@app.route('/', methods=['GET', 'POST'])
def login():
    result = "Not attempted"
    
    if request.method == 'POST':
        result = check_mod()
        
    html = """
        <html>
            <body>
                <h2>Login</h2>
                <form method="post">
                    Username: <input type="text" name="username"><br><br>
                    Password: <input type="password" name="password"><br><br>
                    <button type="submit">Login</button>
                </form>
                <p>{{ result }}</p>
            </body>
        </html>
    """
    
    return render_template_string(html, result=result)

if __name__ == '__main__':
    app.run(debug=True)