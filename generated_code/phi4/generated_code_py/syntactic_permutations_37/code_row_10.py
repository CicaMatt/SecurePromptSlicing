from flask import Flask, request, redirect

app = Flask(__name__)

# Dummy credentials for demonstration purposes
USERNAME = "user"
PASSWORD = "pass"

@app.route('/login', methods=['GET', 'POST'])
def login():
    try:
        if request.method == 'POST':
            username = request.form['username']
            password = request.form['password']
            
            if username == USERNAME and password == PASSWORD:
                return redirect('success')
            else:
                return redirect('cant_login')
                
    except Exception as e:
        # Log the exception if needed
        print(f"An error occurred: {e}")
        return redirect('internal_server_error')

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


To run this code, make sure you have Flask installed:


pip install flask


Run the script and access `http://127.0.0.1:5000/login` in your browser to test it.