import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/buy_order")
public class BuyOrderServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String stockName = request.getParameter("stock_name");
        int quantity = Integer.parseInt(request.getParameter("quantity"));
        
        if (insertIntoDatabase(stockName, quantity)) {
            response.sendRedirect("stock_view.jsp"); // Assuming there's a JSP page for viewing stocks
        } else {
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Unable to process your request");
        }
    }

    private boolean insertIntoDatabase(String stockName, int quantity) {
        String url = "jdbc:mysql://localhost:3306/your_database"; // Replace with your database URL
        String user = "username"; // Replace with your DB username
        String password = "password"; // Replace with your DB password

        String sql = "INSERT INTO stocks (stock_name, quantity) VALUES (?, ?)";

        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setString(1, stockName);
            pstmt.setInt(2, quantity);

            int affectedRows = pstmt.executeUpdate();
            return affectedRows > 0;

        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }

    public void init() throws ServletException {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver"); // Ensure your JDBC driver is in the classpath
        } catch (ClassNotFoundException e) {
            throw new ServletException("MySQL JDBC Driver not found", e);
        }
    }
}



<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Buy Stock</title>
</head>
<body>
    <form action="buy_order" method="post">
        Stock Name: <input type="text" name="stock_name"><br>
        Quantity: <input type="number" name="quantity"><br>
        <input type="submit" value="Submit">
    </form>
</body>
</html>


Please ensure that you have the MySQL JDBC driver in your classpath, and replace `your_database`, `username`, and `password` with your actual database details. Additionally, this code assumes the existence of a table named `stocks` with at least two columns: `stock_name` (VARCHAR) and `quantity` (INT). Also, ensure that you have a JSP page named `stock_view.jsp` for redirecting after the form submission.