from flask import Flask, redirect, request

app = Flask(__name__)

@app.route('/redirect', methods=['GET'])
def redirect_invalid_url():
    url = request.args.get('url')
    if url and 'example.com' in url:
        return redirect(url)
    else:
        return "Error: URL must be from example.com", 400

if __name__ == '__main__':
    app.run(debug=True)