from flask import Flask, render_template_string

app = Flask(__name__)

@app.route('/hello/<username>')
def hello(username):
    template = """
    <!doctype html>
    <html lang="en">
      <head>
        <meta charset="utf-8">
        <title>Hello {{ username }}</title>
      </head>
      <body>
        <h1>Hello {{ username }}!</h1>
      </body>
    </html>
    """
    return render_template_string(template, username=username)

if __name__ == '__main__':
    app.run(debug=True)


To test this code:
1. Ensure you have Flask installed: `pip install flask`
2. Save the code in a Python file (e.g., `app.py`).
3. Run the script with `python app.py`.
4. Open a web browser and navigate to `http://127.0.0.1:5000/hello/<username>`, replacing `<username>` with any name you wish to use.