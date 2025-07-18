package com.login;
import java.util.*;
public class Login{
    public static void main(String[] args){
        Scanner sc= new Scanner(System.in);
        System.out.println("Username");
        String username=sc.nextLine();
        System.out.println("Password");
        String password=sc.nextLine();
        if(username.equalsIgnoreCase("admin")){
            if(password.equals("123456789")){
                System.out.println("Home Page");
            }else{
                System.out.println("Incorrect Password");
            }
        }else{
            System.out.println("User Does not exist");
        }
    }
}