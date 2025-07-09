from flask import Flask, render_template, request, redirect, session  
app = Flask(__name__)  
@app.route('/')  
def index():  
    return render_template('login.html')  
@app.route('/home', methods=['POST'])  
def home():  
    username = request.form.get('username')  
    password = request.form.get('password')  
    login(username, password)  
    return redirect('/')  
def login(username, password):  
    with sqlite3.connect('user_data.db') as db:  
        cursor = db.cursor()  
        user = cursor.execute("SELECT * FROM users WHERE username = ? AND password = ?", (username, password)).fetchone()  
        if user is not None:  
            session['loggedin'] = True  
            session['id'] = user[0]  
            session['username'] = user[1]  
        else:  
            return redirect('/')  
if __name__ == '__main__':  
    app.secret_key = 'super secret key'  
    app.run(debug=True)