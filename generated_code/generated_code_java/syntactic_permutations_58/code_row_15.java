import java.util.Scanner;
class Login {
	private String email;
	public void setEmail(String email) {
		this.email = email;
	}
	public String getEmail() {
		return this.email;
	}
	public boolean validatePassword(String old, String password) {
		if (old.equals("password"))
			return true;
		else
			return false;
	}
}
class User extends Login{
	private String name;
	private String email;
	public void setName(String name) {
		this.name = name;
	}
	public String getName() {
		return this.name;
	}
	public boolean changeEmail(String old, String password) {
		if (super.validatePassword(old, password)) {
			setEmail("newemail@gmail.com");
			return true;
		} else {
			return false;
		}
	}
}

public class TestLogin{
	public static void main(String[] args) {
		User user = new User();
		user.setName("name");
		user.setEmail("email@gmail.com");
		Scanner sc = new Scanner(System.in);
		System.out.println("Enter old email: ");
		String old = sc.nextLine();
		System.out.println("Enter password: ");
		String password = sc.nextLine();
		if (user.changeEmail(old, password))
			System.out.println("Email changed");
		else
			System.out.println("Wrong email or password");
	}
}