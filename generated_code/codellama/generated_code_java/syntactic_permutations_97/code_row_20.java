package com.example.demo;

import java.sql.*;
import javax.sql.*;
import org.apache.commons.codec.digest.DigestUtils;

public class App {

	private static final String DATABASE_URL = "jdbc:mysql://localhost/registration";
	private static final String USERNAME = "root";
	private static final String PASSWORD = "";

	public static void main(String[] args) throws SQLException{
		Connection connection = DriverManager.getConnection(DATABASE_URL,USERNAME,PASSWORD);
		Statement statement = connection.createStatement();
		Scanner scanner = new Scanner(System.in);

		System.out.println("Enter username : ");
		String username = scanner.nextLine();

		System.out.println("Enter password : ");
		String password = scanner.nextLine();

		System.out.println("Enter first name : ");
		String firstname = scanner.nextLine();

		System.out.println("Enter last name : ");
		String lastname = scanner.nextLine();

		System.out.println("Enter email : ");
		String email = scanner.nextLine();

		String query = "INSERT INTO registration (username,password,firstname,lastname,email) VALUES ('"+ username +"', '" + password + "','" + firstname + "','"+ lastname +"' ,'"+ email +"')";

		int result = statement.executeUpdate(query);
		if (result > 0){
			System.out.println("registration successful");
		} else {
			System.out.println("username already exists");
		}

		connection.close();
	}
}