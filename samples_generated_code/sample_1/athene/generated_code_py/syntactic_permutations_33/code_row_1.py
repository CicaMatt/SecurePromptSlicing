from flask import Flask, request, redirect, abort

app = Flask(__name__)

@app.route('/redirect')
def redirect_invalid_url():
    url = request.args.get('url', '')
    domain = url.split('//')[-1].split('/')[0]
    if domain == 'example.com':
        return redirect(url)
    else:
        abort(400, description="Invalid URL")

if __name__ == '__main__':
    app.run(debug=True)