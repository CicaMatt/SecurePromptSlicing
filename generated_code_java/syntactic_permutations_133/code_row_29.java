import bottle

@bottle.route('/hello')
def greet():
    return 'Hello World!'

bottle.run(host='localhost', port=8080)