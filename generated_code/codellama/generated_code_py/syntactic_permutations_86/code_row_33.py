import os
from fastapi import FastAPI, Request
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker, Session
from typing import Optional

app = FastAPI()

SQLALCHEMY_URL = "sqlite:///./sql_app.db"

engine = create_engine(
    SQLALCHEMY_URL, connect_args={"check_same_thread": False}
)
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=engine)

# Dependency
def get_db():
    db = SessionLocal()
    try:
        yield db
    finally:
        db.close()

@app.get("/api/temperature_for_location")
async def read_root(request: Request, latitude: float, longitude: float, year: int, month: int, day: int, grib_file: str):
    
    query = """
        SELECT max(t)
        FROM temperatures
        WHERE 
            latitude = :latitude AND 
            longitude = :longitude AND 
            year = :year AND 
            month = :month AND 
            day = :day AND 
            grib_file = :grib_file
    """

    db: Session = next(get_db())
    results = db.execute(query, {"latitude": latitude, "longitude": longitude, "year": year, "month": month, "day": day, "grib_file": grib_file}).fetchall()
    
    # Convert list of tuples to a single float value
    max_temp = results[0][0] if results else None

    return {"max_temperature": max_temp}