from fastapi import FastAPI, Depends, HTTPException
from sqlalchemy.orm import Session
from . import models
from .database import get_db
from pydantic import BaseModel

app = FastAPI()

class User(BaseModel):
    email: str

@app.post("/unsubscribe")
async def unsubscribe(user: User, db: Session = Depends(get_db)):
    user = db.query(models.User).filter(models.User.email == user.email).first()
    if not user:
        raise HTTPException(status_code=404, detail="Email address not found in database.")
    else:
        db.delete(user)
        db.commit()
    return {"message": "User successfully unsubscribed."}