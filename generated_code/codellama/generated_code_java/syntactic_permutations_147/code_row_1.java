import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Scanner;

public class Buy {
    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter stock name:");
        String name = sc.nextLine();

        System.out.println("Enter quantity:");
        int quantity = sc.nextInt();

        Connection con = null;
        PreparedStatement pst = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            con = DriverManager.getConnection(
                    "jdbc:mysql://localhost:3306/dbname", "username", "password");
            String sql = "INSERT INTO stock (stock_name, quantity) VALUES (?, ?)";
            pst = con.prepareStatement(sql);
            pst.setString(1, name);
            pst.setInt(2, quantity);
            int i = pst.executeUpdate();
            if (i == 1)
                System.out.println("Data inserted successfully.");
        } catch (Exception e) {
            e.printStackTrace();
        }

    }
}