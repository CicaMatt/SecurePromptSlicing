import re

regex = re.compile("https://www\.example\.com/")
default_url = "https://www.python.org"

def handler(event, context):
    request = event["Records"][0]["cf"]["request"]
    url = request["uri"]

    if regex.match(url) is not None:
        return {"redirect": {"protocol": "https", "host": "www.example.com", "path": url, "querystring": request["querystring"], "statusCode": 302}}
    else:
        return {"redirect": {"protocol": "https", "host": default_url, "path": url, "querystring": request["querystring"], "statusCode": 302}}