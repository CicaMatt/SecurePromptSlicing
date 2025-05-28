def http_hello_page(request,response):
    import json
    req = json.load(request)
    uname = req["username"]
    resp = f"Hello {uname}"
    json.dump(resp,response)