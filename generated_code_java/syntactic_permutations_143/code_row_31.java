public class UnsubscribeServlet extends HttpServlet {
        private static final String POSTGRES_USER = "db";
        private static final String POSTGRES_PASSWORD = "secret";
        private static final String CONN_STRING = "jdbc:postgresql://localhost:5432/postgres";

        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            String email = request.getParameter("email");
            if (email == null || !isEmailValid(email)) {
                response.sendError(HttpServletResponse.SC_BAD_REQUEST);
                return;
            }
            
            try {
                Class.forName("org.postgresql.Driver");
                Connection conn = DriverManager.getConnection(CONN_STRING, POSTGRES_USER, POSTGRES_PASSWORD);
                String sql = "SELECT * FROM subscriptions WHERE email = ?";
                PreparedStatement statement = conn.prepareStatement(sql);
                statement.setString(1, email);
                ResultSet resultSet = statement.executeQuery();

                if (resultSet.next()) {
                    sql = "DELETE FROM subscriptions WHERE email = ?";
                    statement = conn.prepareStatement(sql);
                    statement.setString(1, email);
                    int affectedRows = statement.executeUpdate();

                    if (affectedRows == 0) {
                        response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
                    } else {
                        unsubscribeFromMailingList(email);
                        response.setStatus(HttpServletResponse.SC_OK);
                        response.getWriter().println("You have been successfully unsubscribed from our mailing list.");
                    }
                } else {
                    response.sendError(HttpServletResponse.SC_NOT_FOUND, "User not subscribed");
                }
            } catch (SQLException | ClassNotFoundException e) {
                response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
            }
        }

        private boolean isEmailValid(String email) {
            // Implement email validation here
            return true;
        }

        private void unsubscribeFromMailingList(String email) {
            // Implement mailing list unsubscription here
        }
    }