from flask import Flask

app = Flask(__name__)

@app.route('/check')
def check_function():
    # Example logic inside the function
    return "URL triggered the function!"

if __name__ == '__main__':
    app.run(debug=True)