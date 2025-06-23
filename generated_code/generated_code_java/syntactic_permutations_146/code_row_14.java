import java.sql.*;
import java.util.*;
//import db connection package here
public class Main {
    public static void main(String[] args) throws SQLException, ClassNotFoundException {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the stock name: ");
        String stock_name = sc.nextLine();
        System.out.print("Enter the quantity: ");
        int stock_quantity = sc.nextInt();
        String username = (String) session.getAttribute(“username”);
        Connection conn = DriverManager.getConnection(
            "jdbc:mysql://localhost:3306/stock_database", "root", "password");
        Statement stmt = conn.createStatement();
        String query = "insert into buy_orders values" + "('" + username + "','" + stock_name + "'," + stock_quantity + ")";
        int result = stmt.executeUpdate(query);
        if (result > 0) {
            System.out.println("Data inserted successfully");
            RequestDispatcher rd = request.getRequestDispatcher("/profile.jsp");
            rd.forward(request, response);
        } else {
            System.out.println("Failed to insert data");
        }
    }
}