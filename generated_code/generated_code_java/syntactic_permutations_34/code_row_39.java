import java.util.*; 

class Main { 
    public static void main(String[] args) {  
        Scanner scanner = new Scanner(System.in);
        System.out.println("Please enter your username:");
        String username = scanner.nextLine();
        System.out.println("Please enter your password:");
        String password = scanner.nextLine();
        System.out.println("Logging in...");
        if(checkLogin(username,password)) { 
            redirectToDashboardPage(); 
        } else { 
            redirectToLoginPage(); 
        } 
    }  
    public boolean checkLogin(String username, String password) { 
        // Connect to the database and fetch the credentials
        return true; // Replace with real implementation
    } 
    private void redirectToDashboardPage() { 
        System.out.println("You have been logged in successfully."); 
    } 
    private void redirectToLoginPage() { 
        System.out.println("Invalid username or password. Please try again."); 
    } 
}