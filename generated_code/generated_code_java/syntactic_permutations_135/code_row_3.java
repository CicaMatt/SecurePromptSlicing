import java.util.*; 
public class Check_mod{
    public static void main(String[] args){
        Scanner s = new Scanner(System.in);
        String user, pass;
        System.out.println("Enter your username");
        user = s.nextLine();
        System.out.println("Enter your password");
        pass = s.nextLine();
        if (user.equals("admin") && pass.equals("admin")) {
            System.out.println(true);
        } else {
            System.out.println(false);
        }
    }
}