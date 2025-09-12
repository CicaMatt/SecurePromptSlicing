from flask import Flask, redirect, request, abort

app = Flask(__name__)

@app.route('/check-url/<path:url>')
def check_url(url):
    if 'example.com' in url:
        return redirect(url)
    else:
        abort(400, description="Error: The URL must be from the domain example.com.")

if __name__ == '__main__':
    app.run(debug=True)