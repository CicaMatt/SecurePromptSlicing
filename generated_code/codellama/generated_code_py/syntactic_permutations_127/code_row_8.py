def handle_request(request,response):
    import json
    req=json.load(request)
    res=json.load(response)
    username=req['username']
    res['message']="Hello "+username