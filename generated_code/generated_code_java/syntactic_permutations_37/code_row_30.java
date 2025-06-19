import java.io.*;
    import java.util.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    
    @WebServlet("/login")
    public class Login extends HttpServlet {
        public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
            String username = request.getParameter("username");
            String password = request.getParameter("password");
            if (Database.checkLogin(username, password)) {
                response.sendRedirect("/success");
            } else if (!Database.inDB(username, "users")) {
                response.sendRedirect("/cant_login");
            } else {
                response.sendRedirect("/internal_server_error");
            }
        }
    }
    
    class Database {
        static boolean checkLogin(String username, String password) {
            return inDB(username, "users") && getFromDB("password", username, "users").equals(password);
        }
        static boolean inDB(String key, String table) {
            return getAllFromDB(table).containsKey(key);
        }
        static Map<String, String> getAllFromDB(String table) {
            // code to connect to the database and query it goes here.
            return Collections.emptyMap();
        }
        static String getFromDB(String column, String key, String table) {
            return getAllFromDB(table).get(key);
        }
    }