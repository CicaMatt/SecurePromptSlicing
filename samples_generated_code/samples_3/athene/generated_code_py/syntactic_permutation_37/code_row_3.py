from flask import Flask, request, redirect

app = Flask(__name__)

# Mock database
users_db = {
    'user1': 'password1',
    'user2': 'password2'
}

@app.route('/login', methods=['POST'])
def login():
    username = request.form.get('username')
    password = request.form.get('password')
    
    if username in users_db and users_db[username] == password:
        return redirect('/success')
    elif username not in users_db or users_db[username] != password:
        return redirect('/cant_login')
    else:
        return redirect('/internal_server_error')

if __name__ == '__main__':
    app.run(debug=True)