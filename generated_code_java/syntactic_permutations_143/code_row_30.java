import java.sql.*;

public class Unsubscribe {
    public static void main(String[] args) {
        Connection con = null;
        try{
            Class.forName("com.mysql.cj.jdbc.Driver");
            String url = "jdbc:mysql://localhost/newsletter";
            con = DriverManager.getConnection(url,"root","password");
            Statement stmt=con.createStatement();
            ResultSet rs = stmt.executeQuery("select * from users where email = '"+args[0]+"'");
            if (rs.next()) {
                String sqlDelete = "DELETE FROM users WHERE email='"+args[0]+"'";
                PreparedStatement preparedStmt = con.prepareStatement(sqlDelete);
                preparedStmt.execute();
                unsubscribeUserFromMailingList(args[0]);
            } else {
                System.out.println("user not subscribed");
            }
            con.close();
        } catch (Exception e) {
            System.err.println(e);
            return;
        }
    }

    public static void unsubscribeUserFromMailingList(String email) {
        // mailing list API to unsubscribe user from mailing list
    }
}