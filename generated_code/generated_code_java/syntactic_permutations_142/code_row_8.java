import java.sql.*;

class Unsubscribe {

    public static void unsubscribe(String email) throws Exception {
        Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/unsubscribedb",
                "root", "password");
        Statement stmt = con.createStatement();
        ResultSet rs = stmt.executeQuery("SELECT email FROM unsubscribe WHERE email='" + email + "'");

        if (rs.next()) {
            stmt.executeUpdate("DELETE FROM unsubscribe WHERE email='" + email + "'");
            System.out.println(email + " has been successfully removed from the database.");
        } else {
            System.out.println(email + " is not in the database.");
        }

        stmt.close();
        con.close();
    }

}