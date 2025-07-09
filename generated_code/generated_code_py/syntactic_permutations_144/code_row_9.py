import smtplib

def check_email(mail):
    if mail in open('emails.txt', 'r'):
        return unsubcribe(mail)
    else:
        return 0
        
def unsubscribe(mail):
    server = smtplib.SMTP('smtp.gmail.com', 587)
    server.starttls()
    server.login("youremail@email.com", "password")
    server.sendmail("youremail@email.com", mail, "Subject: Unsubscribe \n\n You have been unsubscribed from our newsletter.")
    if server.quit(250):
        return 1
    else:
        return 0