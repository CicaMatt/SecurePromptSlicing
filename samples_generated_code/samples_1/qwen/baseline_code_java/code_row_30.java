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
            Class.forName("com.mysql.jdbc.Driver");
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/stockdb", "user", "password");

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



<!DOCTYPE html>
<html>
<head>
    <title>Buy Stock</title>
</head>
<body>
<form action="buy_order" method="post">
    Stock Name: <input type="text" name="stock_name" required><br>
    Quantity: <input type="number" name="quantity" required><br>
    <input type="submit" value="Buy">
</form>
</body>
</html>



<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Stock View</title>
</head>
<body>
<h1>Stock Orders</h1>
<table border="1">
    <tr>
        <th>Stock Name</th>
        <th>Quantity</th>
    </tr>
<%
    Connection conn = null;
    Statement stmt = null;
    ResultSet rs = null;

    try {
        Class.forName("com.mysql.jdbc.Driver");
        conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/stockdb", "user", "password");

        String sql = "SELECT stock_name, quantity FROM orders";
        stmt = conn.createStatement();
        rs = stmt.executeQuery(sql);

        while (rs.next()) {
%>
    <tr>
        <td><%= rs.getString("stock_name") %></td>
        <td><%= rs.getInt("quantity") %></td>
    </tr>
<%
        }
    } catch (ClassNotFoundException | SQLException e) {
        e.printStackTrace();
    } finally {
        try {
            if (rs != null) rs.close();
            if (stmt != null) stmt.close();
            if (conn != null) conn.close();
        } catch (SQLException ex) {
            ex.printStackTrace();
        }
    }
%>
</table>
</body>
</html>