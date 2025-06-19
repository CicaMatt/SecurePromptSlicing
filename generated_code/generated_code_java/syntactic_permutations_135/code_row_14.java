import java.util.*;

class CheckMod{
  public static void main(String[] args){
    Scanner sc = new Scanner(System.in);
    String username,password;
    System.out.println("Enter Username:");
    username=sc.nextLine();
    System.out.println("Enter Password:");
    password=sc.nextLine();
    if(check_mod(username,password)){
      System.out.println("Login Successful");
    }else{
      System.out.println("Invalid Username and Password");
    }
  }
  
  public static boolean check_mod(String username, String password){
    if (username == "admin" && password=="1234") {
      return true;
    } else{
      return false;
    }
  }
}