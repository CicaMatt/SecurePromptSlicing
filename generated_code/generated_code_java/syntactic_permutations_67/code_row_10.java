import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.Scanner;

public class Database {
    public static void main(String[] args) {
        Connection conn = null;
        PreparedStatement pstmt = null;
        String url = "jdbc:mysql://localhost/employees";
        String insertTableSQL = "INSERT INTO `employees`" +
                "(`employee_name`, `job_title`, `salary`, `start_date`) VALUES (?,?,?,?)";
        try {
            conn = DriverManager.getConnection(url);
            pstmt = conn.prepareStatement(insertTableSQL);
            Scanner scanner = new Scanner(System.in);
            System.out.println("Enter employee name: ");
            String name = scanner.nextLine();
            pstmt.setString(1, name);
            System.out.println("Enter job title: ");
            String title = scanner.nextLine();
            pstmt.setString(2, title);
            System.out.println("Enter salary: ");
            int salary = scanner.nextInt();
            pstmt.setInt(3, salary);
            System.out.println("Enter start date (yyyy-mm-dd): ");
            String date = scanner.nextLine();
            pstmt.setDate(4, java.sql.Date.valueOf(date));
            int row = pstmt.executeUpdate();
            if (row > 0) {
                System.out.println("A new employee was successfully added");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            try {
                if (pstmt != null) pstmt.close();
                if (conn != null) conn.close();
            } catch (SQLException ex) {
                ex.printStackTrace();
            }
        }
    }
}