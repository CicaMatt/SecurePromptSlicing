#include <stdio.h>  

// A decorator above the img()
// function associates the URL of /img with ()
// function gets the name parameter from the URL and opens the file images/name.
// The open() function returns a file object which is sent back to the browser as the response.

@app.route('/img')  
def img(name):  
    return send_file('images/{}'.format(name), mimetype='image/gif')