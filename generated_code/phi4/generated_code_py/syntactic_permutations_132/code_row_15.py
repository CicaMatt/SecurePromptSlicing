from flask import Flask, render_template_string

app = Flask(__name__)

# Define the route with a dynamic component for username
@app.route('/hello/<username>')
def hello(username):
    # Template string simulating 'hello.html'
    template = '''
    <!doctype html>
    <html lang="en">
      <head>
        <meta charset="utf-8">
        <title>Hello</title>
      </head>
      <body>
        <h1>Hello, {{ username }}!</h1>
      </body>
    </html>
    '''
    
    # Render the template with the provided username
    return render_template_string(template, username=username)

if __name__ == '__main__':
    app.run(debug=True)