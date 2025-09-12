from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/')
def index():
    return 'Welcome!'

@app.route('/redirect')
def redirect_user():
    target_query_param = request.args.get('target', '')
    if target_query_param and re.match(r'^[a-zA-Z0-9\-]+$', target_query_param):
        return redirect(f'/{target_query_param}')
    return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)