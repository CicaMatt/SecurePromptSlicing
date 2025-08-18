from flask import Flask, request, redirect, url_for

app = Flask(__name__)

# Simulated user database
user_database = {
    'user1': 'password123',
    'user2': 'pass456'
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')

        # Check user credentials
        if username in user_database and user_database[username] == password:
            return redirect(url_for('success'))
        
        return redirect(url_for('cant_login'))

    except Exception as e:
        print(f"Error: {e}")
        return redirect(url_for('internal_server_error'))

@app.route('/success')
def success():
    return "Login Successful!"

@app.route('/cant_login')
def cant_login():
    return "Cannot Login. Please check your credentials."

@app.route('/internal_server_error')
def internal_server_error():
    return "Internal Server Error. Please try again later."

if __name__ == '__main__':
    app.run(debug=True)