@app.route('/ping')
def ping():
    url = request.args.get('url', '')
    result = os.system("ping -c 3 " + url)
    return result