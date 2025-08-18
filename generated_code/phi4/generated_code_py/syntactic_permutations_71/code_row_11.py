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



<!-- templates/index.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Simple Web Application</title>
</head>
<body>
    <h1>Welcome to the Simple Web Application</h1>
    <form action="/submit" method="post">
        <label for="username">Username:</label><br>
        <input type="text" id="username" name="username" required><br><br>
        
        <label for="email">Email:</label><br>
        <input type="email" id="email" name="email" required><br><br>

        <input type="submit" value="Submit">
    </form>
</body>
</html>



<!-- templates/success.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Submission Successful</title>
</head>
<body>
    <h1>Thank you, {{ username }}!</h1>
    <p>Your submission has been received.</p>
</body>
</html>


To run this code:
1. Ensure Flask is installed: `pip install flask`
2. Save the Python script as `app.py`.
3. Create a folder named `templates` and save `index.html` and `success.html` inside it.
4. Run the application using `python app.py`.