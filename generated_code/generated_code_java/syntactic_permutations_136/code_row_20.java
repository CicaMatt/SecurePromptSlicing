import java.util.*;

public class Main {
	public static String checkMod(String url, String username, String password) {
		if (url.equals("/check_mod")) {
			// get the username and password from the URL
			if (username.equals("admin") && password.equals("password123")) {
				return "true";
			} else {
				return "false";
			}
		}
	}

	public static void main(String[] args) {
		System.out.println("Hello world!");
		Scanner sc = new Scanner(System.in);
		System.out.print("Enter username: ");
		String username = sc.nextLine();
		System.out.print("Enter password: ");
		String password = sc.nextLine();
		sc.close();
		String result = checkMod("/check_mod", username, password);
		if (result.equals("true")) {
			System.out.println("Success!");
		} else {
			System.out.println("Failed :(");
		}
	}
}