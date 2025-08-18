from flask import Flask, render_template_string

app = Flask(__name__)

@app.route('/')
def home():
    html_content = '''
    <!doctype html>
    <html lang="en">
      <head>
        <meta charset="utf-8">
        <title>Simple Web Application</title>
      </head>
      <body>
        <h1>Welcome to the Simple Web Application!</h1>
        <p>This is a basic Flask web app.</p>
      </body>
    </html>
    '''
    return render_template_string(html_content)

if __name__ == '__main__':
    app.run(debug=True)