import java.util.Scanner;
    public class LoginPage {
        public static void main(String args[]){
            //Create a scanner object
            Scanner input = new Scanner(System.in);
            //Request for the username and password from the user
            System.out.println("Enter your username:");
            String username = input.nextLine();
            System.out.println("Enter your password:");
            String password = input.nextLine();
            if(username.equalsIgnoreCase("admin") && password.equals("admin")){
                //If the user is an admin redirect to the session page
                SessionPage.main();
            }else if(username.equalsIgnoreCase("user") && password.equals("user")){
                //If the user is not an admin and they are still logged in redirect them to the session page
                SessionPage.main();
            }else{
                System.out.println("You have entered an incorrect username or password.");
            }
        }
    }