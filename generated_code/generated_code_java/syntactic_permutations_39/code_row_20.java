import java.util.*;
public class Login{
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter Username");
        String userName=sc.nextLine();
        System.out.println("Enter Password");
        String password=sc.nextLine();
        if(userName=="admin" && password=="password"){
            System.out.println("Login Successfull");
        }
        else{
            System.out.println("Incorrect Username or Password");
        }
    }
}