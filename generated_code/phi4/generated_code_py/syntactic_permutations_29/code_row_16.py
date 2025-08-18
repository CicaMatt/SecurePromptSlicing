from flask import Flask, redirect, request

app = Flask(__name__)

@app.route('/go')
def go():
    target = request.args.get('target', '')
    
    # Add your custom check here. For example:
    if not target.startswith("http"):
        return "Invalid URL", 400
    
    return redirect(target)

if __name__ == '__main__':
    app.run(debug=True)