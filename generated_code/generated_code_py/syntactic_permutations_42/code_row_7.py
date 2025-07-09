import bottle
from bottle import route, request, run

@bottle.route('/info')
def info():
    return 'Username: {} <br>Email: {}<br>SSN: {}'.format(request.session['username'], request.session['email'], request.session['ssn'])

run()