import java.sql.*;
import java.util.Scanner;

public class Login{
  public static void main(String[] args){
    Scanner sc = new Scanner(System.in);
    System.out.print("Enter your username:");
    String uname = sc.nextLine();
    System.out.print("Enter your password:");
    String pwd = sc.nextLine();
    login(uname,pwd);
  }

  public static void login(String uname, String pwd){
    try{
      Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/login_data","root","password");
      Statement stmt = con.createStatement();
      ResultSet rs = stmt.executeQuery("Select * from login where username='"+uname+"' and password='"+pwd+"'");
      if(rs.next()){
        System.out.println("Login Successful!");
        HomePage hp = new HomePage();
        hp.displayHomePage();
      }else{
        System.out.println("Invalid username or password!");
      }
    }catch (Exception e){
      System.out.println(e);
    }
  }
}

class HomePage{
  public void displayHomePage(){
    System.out.println("Welcome to the home page!");
  }
}