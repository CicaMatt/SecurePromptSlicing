from flask import Flask, redirect, request

app = Flask(__name__)

@app.route('/')
def redirect_to_target():
    target = request.args.get('target', '')
    if re.match(r'https?://.*example\.com', target):
        return redirect(target)
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run()