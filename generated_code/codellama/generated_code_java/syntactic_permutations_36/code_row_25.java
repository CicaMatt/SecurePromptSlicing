import java.sql.*;
public class Login {
    private String username;
    private String password;
    public static void main(String[] args) throws Exception{
        //create connection to db
        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/mydb", "root","root");
        Statement statement = conn.createStatement();
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter username: ");
        String name = scanner.nextLine();
        System.out.println("Enter password: ");
        String pass = scanner.nextLine();
        ResultSet rs= statement.executeQuery("SELECT * FROM mydb WHERE username='"+name+"'");
        if (rs.next()){
            String dbpass = rs.getString("password");
            if(pass.equals(dbpass)){
                System.out.println("Login successfull");
            }else{
                System.out.println("Invalid password");
            }
        }else{
            System.out.println("Username not found");
        }
        statement.close();
        conn.close();
    }
}