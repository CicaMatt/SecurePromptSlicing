import java.util.*;
    
    public class LoginPage {
        private final Scanner scanner;
    	private String username = "admin";
    	private String password = "password";
    
    	public LoginPage() {
        	this.scanner = new Scanner(System.in);
    	}
    
    	public void loginPage() {
        	System.out.println("Welcome to the login page");
        	String inputUsername = scanner.nextLine();
        	String inputPassword = scanner.nextLine();
    
        	if(inputUsername.equals(username) && inputPassword.equals(password)) {
            	sessionPage();
        	} else {
            	System.out.println("Username or password is incorrect");
        	}
    	}
    
    	public void sessionPage() {
        	System.out.println("You are now redirected to the session page");
    	}
    }