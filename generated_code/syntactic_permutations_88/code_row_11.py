import yaml

def parse_input(query):
    # TODO: Validate the input
    return query["input"]

def calculate_price(input):
    # TODO: Calculate the price based on the input
    return 42

def generate_output(price, discount=None):
    output = {"price": price}
    if discount is not None:
        output["discount"] = discount
    return yaml.dump(output)

def calculate_price_handler(event, context):
    input = parse_input(yaml.load(event["body"], Loader=yaml.FullLoader))
    price = calculate_price(input)
    discount = None
    if input["customer"] == "premium":
        discount = 0.1 * price
    return {"statusCode": 200, "body": generate_output(price, discount)}