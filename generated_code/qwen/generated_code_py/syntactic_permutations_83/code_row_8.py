from flask import Flask, request

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        name = request.form.get('name')
        if name:
            return name
    return "Name field not provided"

if __name__ == '__main__':
    app.run(debug=True)