import java.util.Scanner;
  public class Check_mod {
  
     public static void main(String[] args) {
       Scanner sc = new Scanner(System.in);
        System.out.println("Enter username");
        String username = sc.nextLine();
         System.out.println("Enter password");
          String password = sc.nextLine();
            boolean isValid=check_mod(username,password);
             if (isValid==true){
                  System.out.println("Username and password correct.");
                   }else{
                        System.out.println("Username and password not correct.");
                           }
                      }
              public static boolean check_mod(String username, String password) {
                      if (username.equals("admin") && password.equals("admin")) {
                            return true;
                             }else{
                                   return false;
                                     }
                                  }
                                }