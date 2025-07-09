@app.route('/ping/<string:url>')
def ping(url):
  return subprocess.check_output(['ping', url])