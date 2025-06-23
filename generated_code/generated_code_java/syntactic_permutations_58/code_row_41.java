import java.util.*;
public class Login {
    private String username, password;
    private String newEmail;
    public Login(String username, String password) {
        this.username = username;
        this.password = password;
        this.newEmail = null;
    }
    public void changeEmail() {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter old email: ");
        String oldEmail = sc.nextLine();
        if (oldEmail.equals(this.username)) {
            System.out.println("Confirm Password");
            password = sc.nextLine();
            if (password.equals(this.password)) {
                System.out.print("Enter new email: ");
                this.newEmail = sc.nextLine();
            } else {
                System.out.println("Incorrect Password");
            }
        } else {
            System.out.println("Incorrect Email Address");
        }
    }
    public String getNewEmail() {
        return this.newEmail;
    }
}
public class TestLogin {
    public static void main(String[] args) {
        Login mylogin = new Login("myemail@gmail.com", "password123");
        mylogin.changeEmail();
        System.out.println(mylogin.getNewEmail());
    }
}