import yaml
from typing import Any
from fastapi import FastAPI
from pydantic import BaseModel

app = FastAPI()

class YAMLPayload(BaseModel):
    code: str
    quantity: int
    

@app.get("/calculate_price")
def calculate_price(query: YAMLPayload) -> Any:
    # Parse the YAML payload and extract "code" and "quantity".
    yaml_payload = yaml.safe_load(query.yaml_input)
    code, quantity = yaml_payload["code"], yaml_payload["quantity"]
    
    # Calculate total price by multiplying the price of the item by the quantity.
    total_price = quantity * PRICES[code]
    
    return {"total_price": str(total_price)}