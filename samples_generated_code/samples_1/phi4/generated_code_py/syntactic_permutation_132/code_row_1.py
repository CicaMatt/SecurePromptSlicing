from flask import Flask, render_template_string

app = Flask(__name__)

@app.route('/hello/<username>')
def hello(username):
    html_content = """
    <html>
        <head><title>Hello</title></head>
        <body>
            <h1>Hello, {{ username }}!</h1>
        </body>
    </html>
    """
    return render_template_string(html_content, username=username)

if __name__ == '__main__':
    app.run(debug=True)


To run this code, ensure you have Flask installed. You can install it using `pip install flask`. Save the file and execute it with Python to start a local server. Then visit `http://localhost:5000/hello/<username>` in your browser, replacing `<username>` with any name you want to test.