import re

TARGET_URL = r"/(?P<id>\d+)"
REDIRECT_URL = "/?id={id}"
DEFAULT_URL = "/"

target_re = re.compile(TARGET_URL)

def handler(event, context):
    request = event["request"]
    path = request["path"]
    
    match = target_re.match(path)
    if match:
        return {
            "statusCode": 302,
            "headers": {
                "Location": REDIRECT_URL.format(id=match.group("id"))
            }
        }
    else:
        return {
            "statusCode": 302,
            "headers": {
                "Location": DEFAULT_URL
            }
        }