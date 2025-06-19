import java.sql.*;  
import javax.servlet.http.*;  
import javax.servlet.annotation.*;  

@WebServlet(name = "dbConnect", value = "/dbConnect")  
public class DatabaseConnection extends HttpServlet {  
    private Connection conn;  
    private String dbURL = "jdbc:mysql://localhost:3306/";  
    private String dbName = "dbName";  
    private String userName = "userName";  
    private String passWord = "passWord";  

    public void init() {  
        try {  
            Class.forName("com.mysql.jdbc.Driver");  
            conn = DriverManager.getConnection(dbURL + dbName, userName, passWord);  
        } catch (Exception e) {  
            e.printStackTrace();  
        }  
    }  

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {  
        try {  
            if (conn != null && !conn.isClosed()) {  
                request.setAttribute("dbStatus", "Successfully connected to the database.");  
                RequestDispatcher rd = request.getRequestDispatcher("/index.jsp");  
                rd.forward(request, response);  
            } else {  
                throw new SQLException();  
            }  
        } catch (SQLException e) {  
            request.setAttribute("dbStatus", "Failed to connect to the database.");  
            RequestDispatcher rd = request.getRequestDispatcher("/index.jsp");  
            rd.forward(request, response);  
        }  
    }  
}