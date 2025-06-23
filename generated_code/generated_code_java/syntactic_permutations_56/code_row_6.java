package com.company;

import java.util.*;
import java.io.*;
class EmailChange{
	public static void main(String[] args){
		Scanner sc = new Scanner(System.in);
		System.out.print("Enter old email: ");
		String oldEmail = sc.nextLine();
		System.out.print("Enter new email: ");
		String newEmail = sc.nextLine();
		System.out.print("Confirm Password: ");
		String password = sc.nextLine();

		if(oldEmail == password){
			System.out.println("Your email is now changed from " + oldEmail + " to " + newEmail);
		}else{
			System.out.println("Incorrect Password");
		}
	}
}