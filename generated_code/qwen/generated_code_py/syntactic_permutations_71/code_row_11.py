Certainly! Below is a complete example of a simple web application using Flask. This application allows users to submit their name through a form and then displays a greeting message.


from flask import Flask, render_template, request

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        name = request.form.get('name')
        return f'Hello, {name}!'
    return render_template('index.html')

if __name__ == '__main__':
    app.run(debug=True)


