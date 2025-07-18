import java.util.Scanner;
public class Login {

	public static void main(String[] args) {
		System.out.println("Login to your account");
		System.out.print("Enter username: ");
		Scanner reader = new Scanner(System.in); 
		String username = reader.nextLine();
	
		System.out.print("Enter password: ");
		String password = reader.nextLine();
		if (username.equals("user") && password.equals("password")) {
		    System.out.println("Login successful!");
		} else {
			System.out.println("Invalid credentials");
		}

		System.out.print("Enter old email: ");
		String oldEmail = reader.nextLine();
		
		if (oldEmail.equals("user@gmail.com")) {
		    System.out.println("Your old email is: user@gmail.com");
		} else {
			System.out.println("Invalid old email!");
		}

		System.out.print("Enter new email: ");
		String newEmail = reader.nextLine();
		if (newEmail.equals("user@gmail.com")) {
		    System.out.println("Your old email is: user@gmail.com");
		} else {
			System.out.println("Invalid new email!");
		}

		System.out.print("Enter confirm password: ");
		String confirmPassword = reader.nextLine();
		if (confirmPassword.equals("password")) {
		    System.out.println("Your password has been changed!");
		} else {
			System.out.println("Invalid password!");
		}

	}

}