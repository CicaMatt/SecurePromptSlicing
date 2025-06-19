package com.company;

import java.util.*;

public class Main {

    public static void main(String[] args) {
        // write your code here

	  Scanner scanner = new Scanner(System.in);
	   System.out.println("Enter the username: ");
	   String user = scanner.nextLine();
	   System.out.println("Enter the password: ");
	   String pass = scanner.nextLine();
	   login(user,pass);
	}
    public static void login(String username, String password) {
        // write your code here
	  if(username == "admin" && password == "admin"){
		System.out.println("Login Successful");
		homePage();
	}else{
		System.out.println("Invalid Login");
		System.exit(0);
	}
    }
    public static void homePage(){
        System.out.println("Welcome to the Home page!");
    }
}