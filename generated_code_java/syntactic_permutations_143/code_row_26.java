package com.company;
    import java.util.*;
    import javax.mail.*;
    import javax.mail.internet.*;
    import javax.activation.*;
    public class Mailer 
    {  
        private String host, port, user, pass;  
        private String from, to, sub, unsub, subject, body;  
        private Properties properties;  
        private Session session;  
        // Getters and setters  
        public String getHost() 
        {  
            return host;  
        }  
        public void setHost(String host) 
        {  
            this.host = host;  
        }  
        public String getPort() 
        {  
            return port;  
        }  
        public void setPort(String port) 
        {  
            this.port = port;  
        }  
        public String getUser() 
        {  
            return user;  
        }  
        public void setUser(String user) 
        {  
            this.user = user;  
        }  
        public String getPass() 
        {  
            return pass;  
        }  
        public void setPass(String pass) 
        {  
            this.pass = pass;  
        }  
        public String getFrom() 
        {  
            return from;  
        }  
        public void setFrom(String from) 
        {  
            this.from = from;  
        }  
        public String getTo() 
        {  
            return to;  
        }  
        public void setTo(String to) 
        {  
            this.to = to;  
        }  
        public String getSub() 
        {  
            return sub;  
        }  
        public void setSub(String sub) 
        {  
            this.sub = sub;  
        }  
        public String getUnsub() 
        {  
            return unsub;  
        }  
        public void setUnsub(String unsub) 
        {  
            this.unsub = unsub;  
        }  
        public String getSubject() 
        {  
            return subject;  
        }  
        public void setSubject(String subject) 
        {  
            this.subject = subject;  
        }  
        public String getBody() 
        {  
            return body;  
        }  
        public void setBody(String body) 
        {  
            this.body = body;  
        }  
        // Constructor to initialize all variables  
        public Mailer() 
        {  
            properties = new Properties();  
            properties.put("mail.smtp.auth", "true");  
            properties.put("mail.smtp.starttls.enable", "true");  
            properties.put("mail.smtp.host", getHost());  
            properties.put("mail.smtp.port", getPort());  
            session = Session.getInstance(properties, new javax.mail.Authenticator() 
            {  
                protected PasswordAuthentication getPasswordAuthentication() 
                {  
                    return new PasswordAuthentication(getUser(), getPass());  
                }  
            });  
        }  
        // Function to send an email  
        public synchronized void send() throws MessagingException, UnsupportedEncodingException 
        {  
            MimeMessage message = new MimeMessage(session);  
            message.setFrom(new InternetAddress(from));  
            InternetAddress[] toAddress = { new InternetAddress(to) };  
            // To get the array of addresses  
            for (int i = 0; i < toAddress.length; i++) 
            {  
                message.addRecipient(Message.RecipientType.TO, toAddress[i]);  
            }  
            message.setSubject(subject);  
            // To send HTML mail  
            BodyPart messageBodyPart = new MimeBodyPart();  
            messageBodyPart.setText(body);  
            Multipart multipart = new MimeMultipart();  
            multipart.addBodyPart(messageBodyPart);  
            // Part two is attachment  
            messageBodyPart = new MimeBodyPart();  
            String filename = "filename.txt";  
            DataSource source = new FileDataSource(filename);  
            messageBodyPart.setDataHandler(new DataHandler(source));  
            messageBodyPart.setFileName(filename);  
            multipart.addBodyPart(messageBodyPart);  
            // Put parts in message  
            message.setContent(multipart);  
            Transport transport = session.getTransport("smtp");  
            transport.connect(host, user, pass);  
            transport.sendMessage(message, message.getAllRecipients());  
            transport.close();  
        }  
    }