import java.io.*;
import java.util.Scanner;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;

public class Login {
    private static Connection connection = null;
    
    public static void main(String[] args) {
        try{
            String userName, passWord;
            
            Scanner scanner = new Scanner(System.in);
            System.out.println("Enter username: ");
            userName = scanner.nextLine();
            System.out.println("Enter password: ");
            passWord = scanner.nextLine();
            
            login(userName, passWord);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    
    public static void login(String userName, String passWord) throws Exception{
        try {
            Class.forName("com.mysql.jdbc.Driver");
            connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/login", "root", "password");
            
            Statement statement = connection.createStatement();
            String query = "SELECT * FROM login WHERE username='" + userName + "' AND password='" + passWord + "'";
            ResultSet rs = statement.executeQuery(query);
            if (rs.next()) {
                System.out.println("Redirecting to home page");
                connection.close();
            } else {
                System.out.println("Incorrect username or password");
                return;
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}