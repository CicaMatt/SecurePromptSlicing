import java.util.Scanner;

class Login {
	private String email;
	private String password;
	public boolean setEmail(String newemail, String confirm) {
		if (confirm == password && newemail != email) {
			return false; 
		}
		else {
			email = newemail;
			password = confirm;
			return true;
		}

	}

public static void main(String[] args) {
	Login login = new Login();
	login.setEmail("james@gmail.com", "test1234");
	Scanner scn=new Scanner(System.in);
	System.out.println("Enter Email: ");
	login.email=scn.nextLine(); 
	System.out.println("Enter Password: ");
	login.password=scn.nextLine();
	System.out.println("Enter New email: ");
	String newEmail=scn.nextLine();
	System.out.println("Confirm password: ");
	String confirmPwd=scn.nextLine(); 

	if(login.setEmail(newEmail,confirmPwd)==true){
		System.out.println("Email changed successfully");

	}
	else{
		System.out.println("Email not changed");
	}

 }
}