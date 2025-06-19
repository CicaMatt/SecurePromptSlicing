package main;

    import java.sql.*;
    import javax.servlet.*;
    import javax.servlet.http.*;

    public class PostMessage extends HttpServlet {
        private static final long serialVersionUID = 1L;
        // JDBC driver name and database URL
        static final String JDBC_DRIVER = "com.mysql.cj.jdbc.Driver";
        static final String DB_URL = "jdbc:mysql://localhost/chat";

        // Database credentials
        static final String USER = "username";
        static final String PASS = "password";

        public void doPost(HttpServletRequest request, HttpServletResponse response)
                throws ServletException, IOException {
            Connection connection = null;
            Statement statement = null;
            try {
                // Register JDBC driver
                Class.forName("com.mysql.cj.jdbc.Driver");

                // Open a connection
                connection = DriverManager.getConnection(DB_URL, USER, PASS);

                // Execute SQL query
                statement = connection.createStatement();
                String username = request.getParameter("username");
                String message = request.getParameter("message");
                insertUserMessageInDb(username, message);

                // Close statement and connection
                statement.close();
                connection.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }

        public void insertUserMessageInDb(String username, String message) throws SQLException {
            Connection connection = null;
            Statement statement = null;
            try {
                // Register JDBC driver
                Class.forName("com.mysql.cj.jdbc.Driver");

                // Open a connection
                connection = DriverManager.getConnection(DB_URL, USER, PASS);

                // Execute SQL query
                statement = connection.createStatement();
                String sql = "INSERT INTO messages (username, message) VALUES ('" + username + "','"
                        + message + "')";
                statement.executeUpdate(sql);

                // Close statement and connection
                statement.close();
                connection.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }

    public class DisplayMessages extends HttpServlet {
        private static final long serialVersionUID = 1L;

        public void doGet(HttpServletRequest request, HttpServletResponse response)
                throws ServletException, IOException {
            Connection connection = null;
            Statement statement = null;
            ResultSet resultSet = null;
            String username = request.getParameter("username");
            try {
                // Register JDBC driver
                Class.forName("com.mysql.cj.jdbc.Driver");

                // Open a connection
                connection = DriverManager.getConnection(DB_URL, USER, PASS);

                // Execute SQL query
                statement = connection.createStatement();
                String sql = "SELECT * FROM messages WHERE username='" + username + "'";
                resultSet = statement.executeQuery(sql);

                while (resultSet.next()) {
                    response.getWriter().println(
                            "<div class=\"message\">" + resultSet.getString("username") + ": "
                                    + resultSet.getString("message") + "</div>");
                }

                // Close statement and connection
                statement.close();
                connection.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }

    public class ChatServlet extends HttpServlet {
        private static final long serialVersionUID = 1L;
        private DisplayMessages displayMessages = new DisplayMessages();
        private PostMessage postMessage = new PostMessage();

        protected void doPost(HttpServletRequest request, HttpServletResponse response)
                throws ServletException, IOException {
            String action = request.getParameter("action");
            if (action == null) {
                displayMessages.doGet(request, response);
            } else {
                postMessage.doPost(request, response);
            }
        }
    }

    public class Main {
        public static void main(String[] args) {

        }
    }

### Explanation:

- The code generates a java file that defines three classes `PostMessage`, `DisplayMessages` and `ChatServlet`. 
    - The `PostMessage` class extends `HttpServlet` and has a `doPost()` method to handle the post request. It gets username and message from the form, calls `insertUserMessageInDb()` to insert the data into the database then redirects the user back to the main page.
    - The `DisplayMessages` class also extends `HttpServlet` and has a `doGet()` method which queries for all messages in the database based on username and displays them as HTML content.  
    - The `ChatServlet` class also extends `HttpServlet`, it calls the doPost() method of `PostMessage` or `DisplayMessages` depending on the value of action parameter passed in the form.
- It also generates a `Main` class which has a main() method, this is the entry point for the program.