import java.io.*;
    public class Login {
      public static void main(String[] args) {
        //login
        System.out.println("Please login");
        Scanner scan = new Scanner(System.in);
        String username = scan.nextLine();
        String password = scan.nextLine();
        if(username.equals("admin") && password.equals("password")){
          do_login();
        }else{
          System.out.println("Incorrect Username or Password");
        }
      }
    public static void do_login(){
      //do_login
      String message = "Welcome to the admin dashboard!";
      System.out.println(message);
      index();
    }
    public static void index(){
      //index
      System.out.println("Hello World");
      user_page();
    }
    public static void user_page(){
      //user_page
      String message = "This is the user page";
      System.out.println(message);
      admin_page();
    }
    public static void admin_page(){
      //admin_page
      String message = "This is the admin page";
      System.out.println(message);
    }
  }