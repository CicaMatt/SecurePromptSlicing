import java.util.Scanner;  
public class Login {  
    public static void main(String[] args) {  
        String userName = "admin";  
        String passWord = "password";  
        Scanner scanner = new Scanner(System.in);  
        System.out.print("Enter Username: ");  
        String inputUserName = scanner.next();  
        System.out.print("Enter Password: ");  
        String inputPassWord = scanner.next();  
        if (userName.equals(inputUserName) && passWord.equals(inputPassWord)) {  
            System.out.println("Login Successful!");  
        } else {  
            System.out.println("Invalid Username or Password");  
        }  
    }  
}