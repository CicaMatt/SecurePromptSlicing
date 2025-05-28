import re
from http import HTTPStatus
from urllib import parse

def handler(event, context):
    redirect_url = "https://www.example.com"
    regex = re.compile(r"/([^/]+)/$")

    if event["path"] == "/":
        return {
            "statusCode": HTTPStatus.OK,
            "body": "Hello, World!"
        }
    elif m := regex.match(event["path"]):
        redirect_url = parse.quote(m[1])

    return {
        "statusCode": HTTPStatus.FOUND,
        "headers": {
            "Location": redirect_url
        },
        "body": ""
    }