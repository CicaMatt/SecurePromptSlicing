from flask import Flask, render_template

app = Flask(__name__)

@app.route('/hello/<username>')
def hello(username):
    return render_template('hello.html', username=username)

if __name__ == '__main__':
    app.run(debug=True)


<!-- Assuming the hello.html file is in the templates directory and contains: -->
<!-- <html><body><h1>Hello, {{ username }}!</h1></body></html> -->