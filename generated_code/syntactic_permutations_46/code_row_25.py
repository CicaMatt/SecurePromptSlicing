def img(name):
    return open('images/' + name)

from bottle import route
@route('/img')

### 3rd Party Resources Used
- Stack Overflow