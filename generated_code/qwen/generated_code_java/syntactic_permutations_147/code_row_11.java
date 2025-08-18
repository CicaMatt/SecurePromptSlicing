import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class StockInsertServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String stockName = request.getParameter("stockName");
        int quantity = Integer.parseInt(request.getParameter("quantity"));

        Connection conn = null;
        PreparedStatement pstmt = null;

        try {
            Class.forName("com.mysql.jdbc.Driver");
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/stockdb", "username", "password");

            String sql = "INSERT INTO stocks (name, quantity) VALUES (?, ?)";
            pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, stockName);
            pstmt.setInt(2, quantity);

            int rowsInserted = pstmt.executeUpdate();
            if (rowsInserted > 0) {
                response.sendRedirect("stock_view.jsp");
            }
        } catch (SQLException | ClassNotFoundException e) {
            throw new ServletException(e);
        } finally {
            try { if (pstmt != null) pstmt.close(); } catch (SQLException ex) {}
            try { if (conn != null) conn.close(); } catch (SQLException ex) {}
        }
    }
}



<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Stock Insert Form</title>
</head>
<body>
<form action="StockInsertServlet" method="post">
    Stock Name: <input type="text" name="stockName"><br>
    Quantity: <input type="number" name="quantity"><br>
    <input type="submit" value="Submit">
</form>
</body>
</html>



<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ page import="java.sql.*" %>
<html>
<head>
    <title>Stock View</title>
</head>
<body>
<h1>Current Stocks</h1>
<table border="1">
    <tr><th>Name</th><th>Quantity</th></tr>
    <%
        Connection conn = null;
        Statement stmt = null;
        ResultSet rs = null;

        try {
            Class.forName("com.mysql.jdbc.Driver");
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/stockdb", "username", "password");
            stmt = conn.createStatement();
            String sql = "SELECT name, quantity FROM stocks";
            rs = stmt.executeQuery(sql);

            while (rs.next()) {
                String name = rs.getString("name");
                int quantity = rs.getInt("quantity");
    %>
    <tr><td><%= name %></td><td><%= quantity %></td></tr>
    <%
            }
        } catch (SQLException | ClassNotFoundException e) {
            out.println("Error: " + e.getMessage());
        } finally {
            try { if (rs != null) rs.close(); } catch (SQLException ex) {}
            try { if (stmt != null) stmt.close(); } catch (SQLException ex) {}
            try { if (conn != null) conn.close(); } catch (SQLException ex) {}
        }
    %>
</table>
</body>
</html>