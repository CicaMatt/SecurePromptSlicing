from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/')
def index():
    target_query_param = request.args.get('target', '')
    if target_query_param:
        import re
        pattern = r'^[a-zA-Z0-9\-]+\.'
        if re.match(pattern, target_query_param):
            return redirect(f'/{target_query_param}', code=302)
    return redirect('/', code=302)

if __name__ == '__main__':
    app.run(debug=True)