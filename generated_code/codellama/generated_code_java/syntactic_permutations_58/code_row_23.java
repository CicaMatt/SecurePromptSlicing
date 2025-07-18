import java.util.Scanner;
class LoginSystem { 
    private static String username;
    private static String password;
     public static void main(String[] args) {
         Scanner sc = new Scanner(System.in);
         System.out.println("Enter your email: ");
         username = sc.nextLine();
        System.out.println("Enter your password: ");
         password = sc.nextLine();
        }
     public static boolean login(){
         if(username.equals("")||password.equals("")){
            return false;
         }else{
             return true;
         }
     }
     public static void changeEmail() {
         Scanner sc = new Scanner(System.in);
         System.out.println("Enter your old email: ");
         String oldemail=sc.nextLine();
         if(oldemail.equals(username)){
             System.out.println("Enter new email");
             username=sc.nextLine();
            }else{
                System.out.println("Incorrect email");
                changeEmail();
        }
     }
}