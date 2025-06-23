import java.io.*;
import java.util.*;
class Login{
    private String email, password;

    public void login(String email, String password){
        this.email = email;
        this.password = password;
    }

    public boolean verifyPassword(String password){
        return this.password.equals(password);
    }
}
class User extends Login{
    private String username;
    public void changeEmail(String newEmail, String password){
        if(!verifyPassword(password)){
            System.out.println("Invalid Password");
        }else{
            this.email = newEmail;
        }
    }
}
public class EmailChange {
	public static void main(String[] args) {
		User user1 = new User();
		user1.changeEmail("abc@example.com", "password");
		System.out.println(user1.email);
	}
}