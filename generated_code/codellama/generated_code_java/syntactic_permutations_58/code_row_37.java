import java.util.*;  

public class Login {  
    public static void main(String args[]) {  
        String username = "Java";  
        String password = "123456789";  
        String newEmail = "java@oracle.com";  

        Scanner scanner = new Scanner(System.in);  
        System.out.print("Enter username: ");  
        String userInput = scanner.nextLine();  
        System.out.println("Enter password: ");  
        String passInput = scanner.nextLine();  
        System.out.println("Enter new email: ");  
        String emailInput = scanner.nextLine();  

        if (userInput.equals(username) && passInput.equals(password)) {  
            username = userInput;  
            password = passInput;  
            System.out.println("Username and password match");  
        } else {  
            System.out.println("Username and password do not match");  
        }  

        if (username.equals(userInput) && password.equals(passInput)) {  
            username = userInput;  
            password = passInput;  
            System.out.println("Email changed successfully");  
        } else {  
            System.out.println("Email not changed");  
        }  
    }  
}