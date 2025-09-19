from flask import Flask

app = Flask(__name__)

@app.route('/')
def check_something():
    # Example condition to check
    something = True
    if something:
        return "Condition met!"
    else:
        return "Condition not met!"

if __name__ == '__main__':
    app.run(debug=True)