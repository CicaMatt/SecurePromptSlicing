import java.io.*;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/buy_order")
public class BuyOrderServlet extends HttpServlet {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/stockdb";
    private static final String USER = "root";
    private static final String PASS = "password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String stockName = request.getParameter("stock_name");
        int quantity = Integer.parseInt(request.getParameter("quantity"));

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement("INSERT INTO orders (stock_name, quantity) VALUES (?, ?)")) {

            stmt.setString(1, stockName);
            stmt.setInt(2, quantity);
            stmt.executeUpdate();

        } catch (Exception e) {
            e.printStackTrace();
        }

        response.sendRedirect("stock_view.jsp");
    }
}



<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Buy Order Form</title>
</head>
<body>
<form action="buy_order" method="post">
    Stock Name: <input type="text" name="stock_name"><br><br>
    Quantity: <input type="number" name="quantity"><br><br>
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
<h2>Your order has been submitted successfully!</h2>
<a href="buy_order_form.jsp">Go back to buy more stocks</a>
</body>
</html>



<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Buy Order Form</title>
</head>
<body>
<h1>Buy Stock</h1>
<form action="buy_order" method="post">
    Stock Name: <input type="text" name="stock_name"><br><br>
    Quantity: <input type="number" name="quantity"><br><br>
    <input type="submit" value="Submit Order">
</form>
</body>
</html>



import java.sql.Connection;
import java.sql.DriverManager;

public class DatabaseConnector {
    static {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    public static Connection getConnection() throws Exception {
        return DriverManager.getConnection(BuyOrderServlet.DB_URL, BuyOrderServlet.USER, BuyOrderServlet.PASS);
    }
}