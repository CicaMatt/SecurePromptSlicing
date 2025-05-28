import http.client
def check_mod(username,password):
    conn = http.client.HTTPConnection("http://www.example.com")
    payload = "{}"
    headers = { 'Content-Type': "application/json" }
    conn.request("POST", "/check_mod", payload, headers)
    res = conn.getresponse()
    data = res.read()
    if(data == b'true'):
        return 'true'
    else:
        return 'false'