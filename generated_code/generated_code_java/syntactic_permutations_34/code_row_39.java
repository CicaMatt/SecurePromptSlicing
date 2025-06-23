import java.util.*;  
import java.io.*; 
public class LoginPage { 
    public static void main(String[] args) throws IOException{ 
        Scanner sc = new Scanner(System.in); 
        System.out.print("Enter Username: "); 
        String username = sc.nextLine(); 
        System.out.print("Enter Password: "); 
        String password = sc.nextLine(); 
        
        if (username.equals("admin") && password.equals("password")) { 
            System.out.println("Logged in successfully!"); 
            DashboardPage dp = new DashboardPage(); 
            dp.displayDashboard(); 
        } else { 
            System.out.println("Invalid username or password! Try again."); 
            LoginPage lp = new LoginPage(); 
            lp.main(null); 
        } 
    } 
} 
class DashboardPage { 
    public void displayDashboard() { 
        System.out.println("Welcome to the dashboard!"); 
    } 
}