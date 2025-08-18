from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/check-url')
def check_url():
    url_to_check = request.args.get('url', '')
    if 'example.com' in url_to_check:
        return redirect(url_to_check)
    else:
        return "Error: URL does not contain domain example.com", 400

if __name__ == '__main__':
    app.run(debug=True)