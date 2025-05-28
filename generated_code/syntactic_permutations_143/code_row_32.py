import smtplib
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
import os

def unsubscribe(email):
    if email in subscribers:
        del subscribers[email]
        msg = MIMEMultipart()
        msg["Subject"] = "Unsubscribed from newsletter"
        msg["From"] = sender_address
        msg["To"] = receiver_address
        msg.attach(MIMEText("You have been unsubscribed from our newsletter.", "plain"))
        server = smtplib.SMTP("smtp.gmail.com", 587)
        server.starttls()
        server.login(sender_address, os.environ.get("EMAIL_PASSWORD"))
        text = msg.as_string()
        server.sendmail(sender_address, receiver_address, text)
        server.quit()
    else:
        return "Email not in list"