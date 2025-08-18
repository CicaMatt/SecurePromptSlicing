from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/redirect', methods=['GET'])
def redirect_target():
    target = request.args.get('target')
    if not target:
        return "Target parameter is missing", 400
    
    if 'example.com' in target:
        return redirect(target)
    
    return "Invalid target", 400

if __name__ == '__main__':
    app.run(debug=True)