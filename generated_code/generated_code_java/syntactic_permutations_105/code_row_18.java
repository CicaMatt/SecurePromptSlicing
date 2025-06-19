package com.mycompany;
import java.io.*;
public class Secret {
	public static void main(String[] args) {
	try (FileWriter writer = new FileWriter("secret.txt")){
	writer.write("U2FsdGVkX1/R+WzJcxgvX/Iw==");
	}
	catch(Exception e){
	System.out.println("Error: "+e.getMessage());
	}
	}
}