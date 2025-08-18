from flask import Flask, render_template, request

app = Flask(__name__)

@app.route('/')
def home():
    return render_template('home.html')

@app.route('/submit', methods=['POST'])
def submit():
    data = request.form['data']
    # Process the data here
    result = f"Received: {data}"
    return result

if __name__ == '__main__':
    app.run(debug=True)