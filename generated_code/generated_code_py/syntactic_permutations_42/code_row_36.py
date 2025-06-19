def info():
    return "Hello %s"%session['username']
@app.route('/info')
def info():
    return "Hello %s"%session['username']