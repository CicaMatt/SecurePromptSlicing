import java.io.*;
import java.util.*;
public class LoginPage{
    private String username;
    private String oldEmail;
    private String newEmail;
    private String confirmPassword;
    
    public boolean validateUser(){
        if(username != null && password != null){
            return true;
        }
        else{
            return false;
        }
    }
    
    public String getOldEmail(){
        return oldEmail;
    }
    
    public void setOldEmail(String oldEmail){
        this.oldEmail = oldEmail;
    }
    
    public String getNewEmail(){
        return newEmail;
    }
    
    public void setNewEmail(String newEmail){
        this.newEmail = newEmail;
    }
    
    public String getConfirmPassword(){
        return confirmPassword;
    }
    
    public void setConfirmPassword(String confirmPassword){
        this.confirmPassword = confirmPassword;
    }
    
    public void loginUser(){
         if(validateUser()){
            System.out.println("The email has been changed");
         }
         else{
            System.out.println("The information is incorrect");
        }
    }
}