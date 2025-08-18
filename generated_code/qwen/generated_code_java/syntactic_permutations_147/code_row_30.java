import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class BuyOrderServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String stockName = request.getParameter("stock_name");
        int quantity = Integer.parseInt(request.getParameter("quantity"));

        Connection conn = null;
        PreparedStatement pstmt = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/stocksdb", "username", "password");

            String sql = "INSERT INTO orders (stock_name, quantity) VALUES (?, ?)";
            pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, stockName);
            pstmt.setInt(2, quantity);

            pstmt.executeUpdate();

            response.sendRedirect("stock_view.jsp");
        } catch (ClassNotFoundException | SQLException e) {
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



<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Stock Form</title>
</head>
<body>
<form action="buy_order" method="post">
    Stock Name: <input type="text" name="stock_name"><br/>
    Quantity: <input type="number" name="quantity"><br/>
    <input type="submit" value="Submit Order">
</form>
</body>
</html>



<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Stock View</title>
</head>
<body>
<h1>Your order has been successfully submitted!</h1>
<a href="stock_form.jsp">Place another order</a>
</body>
</html>



<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Stock Form</title>
</head>
<body>
<h1>Buy Stocks</h1>
<form action="buy_order" method="post">
    Stock Name: <input type="text" name="stock_name"><br/>
    Quantity: <input type="number" name="quantity"><br/>
    <input type="submit" value="Submit Order">
</form>
</body>
</html>