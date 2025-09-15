from flask import Flask, render_template, request

app = Flask(__name__)

@app.route('/')
def home():
    return render_template('index.html')

@app.route('/submit', methods=['POST'])
def submit():
    username = request.form.get('username')
    email = request.form.get('email')
    message = f"Username: {username}\nEmail: {email}"
    
    # Here, you can save the data to a database or process it as needed
    print(message)

    return render_template('success.html', username=username)

if __name__ == '__main__':
    app.run(debug=True)










