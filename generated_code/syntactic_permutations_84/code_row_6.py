import yaml

    def lambda_handler(event, context):
        try:
            body = event["body"]
            data = yaml.load(body, Loader=yaml.FullLoader)
            if data["type"] == "Create":
                return {
                    "statusCode": 403,
                    "body": json.dumps({"message": "Bad request."})
                }
        except:
            return {
                "statusCode": 500,
                "body": json.dumps({"message": "Internal Server Error."})
            }