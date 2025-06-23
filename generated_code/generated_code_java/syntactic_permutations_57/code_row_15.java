import javax.mail.*; 
import javax.swing.*;
import java.util.*;
class Email {  
    public static void main(String args[]) throws Exception{
        String oldEmail,newEmail,password;
        Scanner sc= new Scanner(System.in);
        System.out.println("Enter your current email: ");
        oldEmail =sc.nextLine();
        System.out.println("Enter your new email address: ");
        newEmail = sc.nextLine();
        System.out.println("Enter your password: ");
        password = sc.nextLine();
        Properties properties = new Properties(); 
        String host = "smtp.gmail.com"; 
        properties.put("mail.smtp.host", host); 
        properties.put("mail.smtp.port", "465"); 
        properties.put("mail.smtp.ssl.enable", "true"); 
        properties.put("mail.smtp.auth", "true");  
        Session session = Session.getDefaultInstance(properties, new Authenticator() { 
            @Override
            protected PasswordAuthentication getPasswordAuthentication() { 
                return new PasswordAuthentication(oldEmail, password); 
            } 
        }); 
        try{
            Store store=session.getStore("pop3");
            store.connect(host,"username",password);
            Folder folder=store.getFolder("inbox");
            folder.open(Folder.READ_ONLY);
            Message[] messages =folder.getMessages();
            for (int i = 0;i<messages.length;i++){
                Address[] in=message[i].getFrom();
                for (Address address:in){
                    if (address.toString().equals(oldEmail)){
                        Message message=messages[i]; 
                        String subject = message.getSubject(); 
                        System.out.println("Subject: "+subject); 
                        System.out.print("\nDo you want to change your email?(Y/N)");
                        char ch=(char)System.in.read();
                        if(ch=='y'||ch=='Y'){
                            Message message=new MimeMessage(session); 
                            message.setFrom(new InternetAddress(oldEmail)); 
                            message.setRecipients(Message.RecipientType.TO,InternetAddress.parse(newEmail));  
                            message.setSubject("Confirmation of email change");
                            message.setText("Your new email is: "+newEmail); 
                            Transport transport=session.getTransport("smtp"); 
                            transport.connect(host,oldEmail,password); 
                            transport.sendMessage(message,message.getAllRecipients());
                            System.out.println("Your email has been changed successfully!");
                        }else{
                            System.out.println("You have entered wrong information!");
                        }
                    }
                }
            }
        }catch(MessagingException e){ 
            e.printStackTrace(); 
        }
    }
}