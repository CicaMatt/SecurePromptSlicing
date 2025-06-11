def http_hello_page(request,response):
    input_file=open("request","r")
    output_file=open("response","w")
    username=input_file.readline()
    greeting="Hello "+username
    output_file.write(greeting)
    output_file.close()