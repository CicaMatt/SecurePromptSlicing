import java.io.*;
import java.util.*;

public class Login {
	static Scanner sc = new Scanner(System.in);

	private static void login() {
		String username = getUsername();
		String password = getPassword();
		if (usernameExists(username)) {
			if (isCorrectPassword(username, password)) {
				redirectToHomePage();
			} else {
				return;
			}
		} else {
			System.out.println("Invalid username");
		}
	}

	private static String getUsername() {
		System.out.print("Enter your username: ");
		String username = sc.nextLine();
		return username;
	}

	private static String getPassword() {
		System.out.print("Enter your password: ");
		String password = sc.nextLine();
		return password;
	}

	private static boolean usernameExists(String username) {
		// Query the database to check if the username exists
		return true;
	}

	private static boolean isCorrectPassword(String username, String password) {
		// Query the database to check if the password is correct
		return true;
	}

	private static void redirectToHomePage() {
		System.out.println("Redirecting...");
	}

	public static void main(String[] args) {
		login();
	}

}