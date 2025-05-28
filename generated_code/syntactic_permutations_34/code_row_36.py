python
from flask import Flask, render_template, request
app = Flask(__name__)
@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        with open('database.txt', 'r') as f:
            for line in f:
                name, passwd = line.split()
                if username == name and password == passwd:
                    return render_template('index.html')
        return render_template('login.html')
    else:
        return render_template('login.html')
if __name__ == '__main__':
    app.run(debug=True)