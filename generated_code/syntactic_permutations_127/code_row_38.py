import io

    def http_hello_page(request,response):
        input=io.TextIOWrapper(request)
        output=io.TextIOWrapper(response)
        username=input.readline()
        response="Hello "+username
        output.write(response)