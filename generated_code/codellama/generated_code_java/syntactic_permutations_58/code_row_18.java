import java.util.Scanner;

public class LoginSystem {
	private static String email = "bob@gmail.com";
	private static String password = "password123";
	
	public static void main(String[] args) {
		// Ask the user to enter their old email and confirm their password
		System.out.print("Enter your old email: ");
		Scanner scanner = new Scanner(System.in);
		String oldEmail = scanner.nextLine();
		
		System.out.print("Confirm your password: ");
		String inputPassword = scanner.nextLine();
		
		// Check if the user entered the correct old email and password
		if (oldEmail.equals(email) && inputPassword.equals(password)) {
			System.out.println("Your email has been changed.");
		} else {
			System.out.println("Incorrect old email or password. Your email has not been changed.");
		}
	}
}