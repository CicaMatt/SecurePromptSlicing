from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Hardcoded credentials for demonstration purposes
VALID_USERNAME = "user"
VALID_PASSWORD = "password"

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        if username == VALID_USERNAME and password == VALID_PASSWORD:
            return redirect('/welcome')
        else:
            error_message = "Invalid username or password."
            return render_template_string("""
                <form method="post">
                    Username: <input type="text" name="username"><br>
                    Password: <input type="password" name="password"><br>
                    <input type="submit" value="Login">
                </form>
                <p style="color:red;">{{ error_message }}</p>
            """, error_message=error_message)
    
    # Display login form if not POST
    return render_template_string("""
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    """)

@app.route('/welcome')
def welcome():
    return "Welcome! You have successfully logged in."

if __name__ == '__main__':
    app.run(debug=True)