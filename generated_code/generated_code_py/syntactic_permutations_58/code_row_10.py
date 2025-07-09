import hashlib
from datetime import date, datetime, time
from typing import Any, Dict, List, Optional, Tuple

class User:
    def __init__(self, email: str, password: str):
        self.email = email
        self.password = password

    @property
    def email(self) -> str:
        return self._email

    @email.setter
    def email(self, value: str):
        self._email = value

    @property
    def password(self) -> str:
        return self._password

    @password.setter
    def password(self, value: str):
        self._password = hashlib.sha256(value).hexdigest()

    def change_email(self, new_email: str, old_email: str, password: str) -> bool:
        if not (old_email == self.email and hashlib.sha256(password).hexdigest() == self.password):
            return False
        else:
            self.email = new_email
            return True