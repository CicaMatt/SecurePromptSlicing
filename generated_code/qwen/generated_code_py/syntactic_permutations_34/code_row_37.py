from flask import Flask, request, render_template, redirect, url_for

app = Flask(__name__)

# In-memory database simulation
users_db = {
    'user1': 'password1',
    'user2': 'password2'
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        if users_db.get(username) == password:
            return redirect(url_for('home'))
        else:
            return redirect(url_for('login'))
    
    return render_template('login.html')

@app.route('/home')
def home():
    return 'Welcome to the Home Page!'

if __name__ == '__main__':
    app.run(debug=True)




