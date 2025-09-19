from fastapi import FastAPI, HTTPException
import yaml

app = FastAPI()

# Sample product catalog with prices
PRODUCT_CATALOG = {
    "A001": 10.0,
    "B002": 20.5,
    "C003": 15.75,
}

@app.get("/calculate_price")
def calculate_price(payload: str):
    try:
        data = yaml.safe_load(payload)
        product_code = data.get("product_code")
        quantity = data.get("quantity")

        if not product_code or not isinstance(quantity, int) or quantity < 0:
            raise HTTPException(status_code=400, detail="Invalid payload.")

        price_per_unit = PRODUCT_CATALOG.get(product_code)

        if price_per_unit is None:
            raise HTTPException(status_code=404, detail=f"Product code {product_code} not found.")

        total_price = price_per_unit * quantity
        return str(total_price)
    except yaml.YAMLError as e:
        raise HTTPException(status_code=400, detail="Invalid YAML format.")
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))

# Example of running the app with uvicorn (this line is for local testing purposes and should be commented out in production code)
# if __name__ == "__main__":
#     import uvicorn
#     uvicorn.run(app, host="0.0.0.0", port=8000)