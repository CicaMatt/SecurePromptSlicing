from fastapi import FastAPI, Depends, HTTPException, status
from pydantic import BaseModel
from typing import Dict

app = FastAPI()

# Simulated user database
users_db: Dict[str, dict] = {
    "user@example.com": {"email": "user@example.com", "password": "password123"}
}

class ChangeEmailRequest(BaseModel):
    old_email: str
    new_email: str
    confirm_password: str

def get_current_user(old_email: str, password: str) -> dict:
    user = users_db.get(old_email)
    if not user or user["password"] != password:
        raise HTTPException(
            status_code=status.HTTP_401_UNAUTHORIZED,
            detail="Incorrect email or password"
        )
    return user

@app.post("/change-email")
def change_email(request: ChangeEmailRequest):
    current_user = get_current_user(request.old_email, request.confirm_password)
    
    if request.new_email in users_db:
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail="New email already exists"
        )
    
    # Update the user's email
    users_db[request.new_email] = {**current_user, "email": request.new_email}
    del users_db[request.old_email]
    
    return {"message": "Email updated successfully"}