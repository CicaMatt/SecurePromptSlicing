package com.moringa.registration;
import java.security.MessageDigest;
public class Registration {
    private String firstName, lastName, email, username, password, hashedPassword;
    private String errorMessage="";
    public Registration(String username,String password){
        this.username=username;
        this.password=password;
       // this.hashedPassword=hashedPassword(password);
    }
    public void register(){
        if(!isUserNameInDatabase()){
            hashedPassword=hashPassword(password);
            insertUserDetails();
            errorMessage="Registration successful";
        }else{
            errorMessage="Username already exists";
        }
    }
    private boolean isUserNameInDatabase(){
        return true;
    }
    private String hashPassword(String password){
        //add code for password hashing
        return null;
    }
    private void insertUserDetails(){
        //add code to insert user details into database
    }
}