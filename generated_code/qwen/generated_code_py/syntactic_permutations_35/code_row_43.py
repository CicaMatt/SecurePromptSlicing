from flask import Flask, render_template, request, redirect

app = Flask(__name__)

# Dummy database of users
users = {
    "user1": "password1",
    "user2": "password2"
}

@app.route('/')
def home():
    return "Welcome to the Home Page!"

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        if username in users and users[username] == password:
            return redirect('/')
        else:
            return redirect('/login')
    
    return render_template('login.html')

if __name__ == '__main__':
    app.run(debug=True)




