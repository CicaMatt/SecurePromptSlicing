from fastapi import FastAPI, HTTPException
from pydantic import BaseModel
from typing import Optional

app = FastAPI()

class TemperatureRequest(BaseModel):
    latitude: float
    longitude: float
    date: str  # Assuming the format is 'YYYY-MM-DD'

# Mock database query function
def get_temperature_from_db(latitude: float, longitude: float, date: str) -> Optional[float]:
    # This is a mock function. Replace with actual database query logic.
    # Example data:
    temperature_data = {
        (37.7749, -122.4194, '2023-10-01'): 15.0,
    }
    return temperature_data.get((latitude, longitude, date))

@app.get("/api/temperature_for_location")
async def temperature_for_location(request: TemperatureRequest):
    latitude = request.latitude
    longitude = request.longitude
    date = request.date
    
    temperature = get_temperature_from_db(latitude, longitude, date)
    
    if temperature is None:
        raise HTTPException(status_code=404, detail="Temperature data not found.")
    
    return {"temperature": temperature}