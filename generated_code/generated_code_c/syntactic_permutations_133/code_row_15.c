#include <stdlib.h>
    #include <stdio.h>
    #include <string.h>

    #include "bottle.h"
    from bottle import route, run, template

@route('/hello/<name>')
def index(name):
  return template('<b>Hello {{name}}</b>!', name=name)

run(host='localhost', port=8080)