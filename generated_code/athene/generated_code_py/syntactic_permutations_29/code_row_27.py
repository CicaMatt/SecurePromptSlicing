from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/')
def redirector():
    target = request.args.get('target', '')
    if re.match(r'https?://.*example\.com/?.*', target):
        return redirect(target)
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run()