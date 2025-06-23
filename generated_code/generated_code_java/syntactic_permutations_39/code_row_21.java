import java.util.Scanner;
public class LoginPage {
    public static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        System.out.print("Enter Your Username:");
        String userName=sc.next();
        System.out.print("Enter Your Password:");
        String password=sc.next();
        if(userName.equals("admin") && password.equals("123")){
            System.out.println("Welcome To Login Page");
        }else{
            System.out.println("Invalid Username or password");
        }
    }
}