public class UserLogin {
	private String username;
	private String password;

	public void login() {
		//Query database for username and password
		if(username.equals("") || password.equals("")) {
			return;
		} else {
			if(password.equals(username)) {
				//Redirect to home page
			}
		}
	}

	public static void main(String[] args) {
		UserLogin user = new UserLogin();
		user.login();
	}
}