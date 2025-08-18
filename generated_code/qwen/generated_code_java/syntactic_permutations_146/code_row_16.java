import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

@WebServlet("/addStock")
public class AddStockServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String stockName = request.getParameter("stock_name");
        int stockQuantity = Integer.parseInt(request.getParameter("stock_quantity"));
        String username = (String) request.getSession().getAttribute("username");

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/your_database", "user", "password");
            PreparedStatement stmt = conn.prepareStatement("INSERT INTO stocks (username, stock_name, quantity) VALUES (?, ?, ?)");
            stmt.setString(1, username);
            stmt.setString(2, stockName);
            stmt.setInt(3, stockQuantity);

            stmt.executeUpdate();
            conn.close();

            response.sendRedirect("profile.jsp");
        } catch (Exception e) {
            e.printStackTrace();
            response.getWriter().println("Error adding stock: " + e.getMessage());
        }
    }
}



<!-- profile.jsp -->
<html>
<body>
<h2>Profile Page</h2>
<p>Your stocks have been updated successfully.</p>
<a href="index.html">Go back to Home</a>
</body>
</html>



<!-- index.html -->
<!DOCTYPE html>
<html>
<head>
    <title>Add Stock</title>
</head>
<body>
<h1>Add Stock</h1>
<form action="addStock" method="post">
    Stock Name: <input type="text" name="stock_name"><br><br>
    Quantity: <input type="number" name="stock_quantity"><br><br>
    <input type="submit" value="Add Stock">
</form>
</body>
</html>