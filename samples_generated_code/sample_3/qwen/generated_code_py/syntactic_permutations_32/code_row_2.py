from flask import Flask, redirect, abort
import validators

app = Flask(__name__)

@app.route('/redirect/<url>')
def redirect_invalid_url(url):
    if validators.url(url):
        return redirect(url)
    else:
        abort(400)

if __name__ == '__main__':
    app.run(debug=True)