import java.util.*;  
class Email{  
    public static String changeEmail(String oldEmail, String password, String newEmail){  
        if(password.equals("") || oldEmail.equals("")){  
            return "Error: Password or old email is empty";  
        }  
        else if(oldEmail != null && oldEmail.equals(password)){  
            return "Error: Old password and old email do not match";  
        }  
        else{  
            return newEmail;  
        }  
    }  
}  
public class EmailChangeLogSystem {  
   public static void main(String args[]){  
      String oldEmail = "john.doe@example.com";  
      String password = "pass1234";  
      String newEmail = "jane.doe@example.com";  
      System.out.println(Email.changeEmail(oldEmail, password, newEmail));  
   }  
}