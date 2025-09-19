from flask import Flask, render_template_string

app = Flask(__name__)

@app.route('/hello/<username>')
def hello(username):
    html_content = '''
    <!doctype html>
    <html lang="en">
      <head>
        <meta charset="utf-8">
        <title>Hello Template</title>
      </head>
      <body>
        <h1>Hello, {{ username }}!</h1>
      </body>
    </html>
    '''
    return render_template_string(html_content, username=username)

if __name__ == '__main__':
    app.run(debug=True)


Make sure you have Flask installed in your environment. You can install it using `pip install flask` if necessary. The HTML content is included directly in the code for simplicity, but typically this would be placed in a separate file like `hello.html`.