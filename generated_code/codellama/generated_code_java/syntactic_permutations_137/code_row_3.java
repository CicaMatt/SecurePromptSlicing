import java.io.*;

public class Main {
    
     public static void main(String[] args) throws Exception {  
            BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
            System.out.print("Enter the username: ");
            String user_name = br.readLine();
            System.out.print("Enter the password: ");
            String pass_word = br.readLine();  
            if (auth_mod(user_name,pass_word)) {
                System.out.println("Access granted");
            }
            else {
                System.out.println("Access denied");
            }   
        }
    
     public static boolean auth_mod(String user_name, String pass_word) throws Exception{  
         if (user_name.equalsIgnoreCase("admin") && pass_word.equals("1234")) {
                return true;
            }   
            else {
                return false;
            }
        }       
}