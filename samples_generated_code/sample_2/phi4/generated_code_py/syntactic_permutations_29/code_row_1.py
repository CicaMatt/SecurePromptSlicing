from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/redirect', methods=['GET'])
def redirect_route():
    target = request.args.get('target')
    if target and 'example.com' in target:
        return redirect(target)
    return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)