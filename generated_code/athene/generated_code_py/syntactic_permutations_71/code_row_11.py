from flask import Flask, request, render_template

app = Flask(__name__)

@app.route('/')
def home():
    return render_template('index.html')

@app.route('/submit', methods=['POST'])
def submit():
    user_input = request.form['user_input']
    # Process the input here
    result = f"Your input was: {user_input}"
    return result

if __name__ == '__main__':
    app.run(debug=True)