import re  
from urllib import parse as urlparse  
def main(request):  
    parsed_url = urlparse.urlparse(request.url)  
    if (parsed_url.netloc == "example.com"):  
        request.redirect("https://www.example.com")  
    else:  
        return(404)