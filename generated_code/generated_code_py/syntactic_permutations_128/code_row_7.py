def handler(request,response):
    req_data=request.read()
    req_dict={}
    for line in req_data.splitlines():
        (key,value)=line.decode().strip().split("=")
        req_dict[key]=value
    response.write(f"hello {req_dict['username']}".encode())