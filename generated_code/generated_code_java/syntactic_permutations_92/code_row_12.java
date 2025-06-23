package com.registerform;
import java.util.*;
public class RegisterForm {
    private String username;
    private String password;
    Scanner input = new Scanner(System.in);
    public void setUsername() {
        System.out.println("Enter Username: ");
        username = input.nextLine();
    }
    public void setPassword() {
        System.out.println("Enter Password: ");
        password = input.nextLine();
    }
}