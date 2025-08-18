import java.io.IOException;
import java.util.List;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.sql.DataSource;
import org.apache.commons.dbutils.QueryRunner;
import org.apache.commons.dbutils.handlers.BeanListHandler;

@WebServlet("/sendMessage")
public class SendMessageServlet extends HttpServlet {

    private DataSource dataSource;

    @Override
    public void init() throws ServletException {
        // Initialize the data source, replace with your actual data source initialization code.
        this.dataSource = (DataSource) getServletContext().getAttribute("dataSource");
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        String username = request.getParameter("username");
        String message = request.getParameter("message");

        if (insertUserMessageInDB(username, message)) {
            response.sendRedirect("/");
        } else {
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Failed to save the message.");
        }
    }

    private boolean insertUserMessageInDB(String username, String message) {
        try {
            QueryRunner queryRunner = new QueryRunner(dataSource);
            return queryRunner.update(
                "INSERT INTO messages (username, message) VALUES (?, ?)", 
                username, message
            ) > 0;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }

    @WebServlet("/viewMessages")
    public static class ViewMessagesServlet extends HttpServlet {

        private DataSource dataSource;

        @Override
        public void init() throws ServletException {
            this.dataSource = (DataSource) getServletContext().getAttribute("dataSource");
        }

        protected void doGet(HttpServletRequest request, HttpServletResponse response)
                throws ServletException, IOException {

            try {
                QueryRunner queryRunner = new QueryRunner(dataSource);
                List<Message> messages = queryRunner.query(
                    "SELECT username, message FROM messages", 
                    new BeanListHandler<>(Message.class)
                );

                request.setAttribute("messages", messages);
                request.getRequestDispatcher("/viewMessages.jsp").forward(request, response);

            } catch (Exception e) {
                e.printStackTrace();
                response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Failed to retrieve the messages.");
            }
        }

        public static class Message {
            private String username;
            private String message;

            // Getters and setters
            public String getUsername() { return username; }
            public void setUsername(String username) { this.username = username; }
            public String getMessage() { return message; }
            public void setMessage(String message) { this.message = message; }
        }
    }
}


Ensure you have a `DataSource` configured in your servlet context, and create the corresponding JSP page (`viewMessages.jsp`) to display messages.