import os
from dotenv import load_dotenv
load_dotenv()

import sendgrid
from sendgrid.mail import Mail
from sendgrid.sendgrid import SendGridAPIClient
from sendgrid.helpers.mail import Email, To, Content

# Create a new instance of the API class
sg = sendgrid.SendGridAPIClient(apikey=os.environ.get("SENDGRID_API_KEY"))

def unsubscribe(email):
    if email in os.environ.get("EMAIL_LIST"):
        os.environ.get("EMAIL_LIST").remove(email)
        message = Mail()
        message.to = Email(email)
        message.from_email = Email("admin@example.com")
        message.subject = "Unsubscribe Successful"
        content = Content("text/plain", "You have been unsubscribed from our mailing list.")
        message.add_content(content)
        sg.send(message)
    else:
        print("User is not subscribed")