import java.util.*;
import java.io.*;

public class Unsubscribe {
    private String email;
    
    public Unsubscribe(String email){
        this.email = email;
    }
    public void unsubsribe(){
        Database db = new Database();
        if(db.checkEmail(email)){
            db.removeEmail(email);
            System.out.println("You have been successfully unsubscribed");
        } else {
            System.out.println("You are not in the database");
        }
    }
}
public class Database {
    private List<String> emails;
    
    public Database(){
        emails = new ArrayList<>();
    }
    public void addEmail(String email){
        emails.add(email);
    }
    public boolean checkEmail(String email){
        return emails.contains(email);
    }
    public void removeEmail(String email){
        emails.remove(email);
    }
}