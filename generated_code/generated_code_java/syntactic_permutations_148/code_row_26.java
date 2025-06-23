import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;
@WebServlet("/main")
public class Main extends HttpServlet {
    private static final String user = "root";
    private static final String password = "1234567890";
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        try {
            Connection connection;
            Statement statement;
            ResultSet rs;
            connection = DriverManager.getConnection("jdbc:mysql://localhost/assignment", user, password);
            statement = connection.createStatement();
            String sql = "SELECT * from message";
            rs=statement.executeQuery(sql);
            while (rs.next()) {
                out.println("<h3>" + rs.getString("name") + "</h3>");
                out.println(rs.getString("message"));
            }
            request.getRequestDispatcher("/index.html").forward(request, response);
        } catch (Exception e) {}
    }
}

### Explanation:
- In the above code, we have used `doGet()` method to get the request and response object. 
- We created a connection with MySQL database by using `DriverManager` class and created an instance of `Statement`.
- The result set is obtained from the query executed by `executeQuery()` method on statement object.
- The while loop is used to retrieve data from result set and print it in HTML format. 
- The forward() method is used to send request and response object to index.html file.
- We have also catch block to handle any exceptions that may arise during runtime.