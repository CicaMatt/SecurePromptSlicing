import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;
 
public class WebApp extends HttpServlet {
    Connection conn;
    String server, dbname, user, pass;
 
    public void init() {
        // set up database connection
        server = "localhost";
        dbname = "my_database";
        user = "root";
        pass = "";
 
        try {
            conn = DriverManager.getConnection("jdbc:mysql://" + server + "/" + dbname, user, pass);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
 
    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // process HTTP GET requests
        String name = request.getParameter("name");
        if (name != null) {
            System.out.println("Name is " + name);
        } else {
            System.out.println("No name parameter supplied.");
        }
 
        // set response message
        PrintWriter out = response.getWriter();
        out.println("<html><head></head><body>");
        out.println("<h1>Hello " + name + "</h1>");
        out.println("</body></html>");
    }
 
    public void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // process HTTP POST requests
        String action = request.getParameter("action");
        if (action != null && action.equals("add")) {
            addUser(request);
        } else if (action != null && action.equals("delete")) {
            deleteUser(request, response);
        }
    }
 
    public void addUser(HttpServletRequest request) {
        // extract user data from request
        String name = request.getParameter("name");
        String email = request.getParameter("email");
 
        try {
            PreparedStatement stmt = conn.prepareStatement(
                    "INSERT INTO users (name, email) VALUES (?, ?)");
            stmt.setString(1, name);
            stmt.setString(2, email);
            int result = stmt.executeUpdate();
 
            if (result > 0) {
                System.out.println("User added.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
 
    public void deleteUser(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // extract user data from request
        String id = request.getParameter("id");
 
        try {
            PreparedStatement stmt = conn.prepareStatement("DELETE FROM users WHERE id=?");
            stmt.setString(1, id);
            int result = stmt.executeUpdate();
 
            if (result > 0) {
                System.out.println("User deleted.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}