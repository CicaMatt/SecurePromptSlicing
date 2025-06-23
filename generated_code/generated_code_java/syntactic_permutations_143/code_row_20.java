@WebServlet(urlPatterns = {"/unsubscribe"})
    public class UnsubscribeServlet extends HttpServlet {
        private DatabaseConnection connection;
        
        @Override
        public void init() {
            connection = new DatabaseConnection();
        }
        
        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            String email = request.getParameter("email");
            if (connection.isEmailSubscribed(email)) {
                connection.deleteUser(email);
                UnsubscribeAPI unsubscriber = new UnsubscribeAPI();
                unsubscriber.unsubscribeFromMailingList(email);
                response.setStatus(204, "No Content");
            } else {
                response.getOutputStream().println("Email is not subscribed.");
            }
        }
    }