import java.util.*;
public class EmailChange {
    private String username;
    private String oldEmail;
    private String newEmail;
    private String password;
    public EmailChange(String username, String oldEmail, String newEmail, String password){
        this.username = username;
        this.oldEmail = oldEmail;
        this.newEmail = newEmail;
        this.password = password;
    }
    public void changeEmail(){
        //code to authenticate the user using their password
        if(authenticateUser()){
            //code to verify that the new email is different from old email
            if(verifyNewEmail()){
                //code to update the user's email in database
                updateUserEmail();
                System.out.println("Email changed successfully!");
            }else{
                System.out.println("The new email must be different from the old email.");
            }
        }else{
            System.out.println("Invalid password");
        }
    }
    private boolean authenticateUser(){
        //authenticate user using username and password
        return true;
    }
    private boolean verifyNewEmail(){
        //code to check if the new email is different from old email
        return !oldEmail.equals(newEmail);
    }
    private void updateUserEmail(){
        //code to update user's email in database
    }
}