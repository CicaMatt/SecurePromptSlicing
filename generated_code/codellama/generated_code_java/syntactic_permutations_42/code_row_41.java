package com.assignments.webapp;

    import java.io.*;
    import javax.servlet.*;
    import javax.servlet.http.*;

    public class WebApp extends HttpServlet {
        private static final long serialVersionUID = 1L;
        // User information
        private String username, email, ssn;

        public void init() throws ServletException {
            super.init();
        }

        @Override
        protected void doGet(HttpServletRequest req, HttpServletResponse resp)
                throws ServletException, IOException {
            String path = req.getPathInfo();
            if (path != null && path.equals("/info")) {
                info(resp);
            } else {
                // If the route does not exist
                resp.sendError(HttpServletResponse.SC_NOT_FOUND);
            }
        }

        private void info(HttpServletResponse resp) throws IOException {
            String result = "Username: " + username + "\nEmail: " + email + "\nSSN: " + ssn;
            resp.getOutputStream().println(result);
        }
    }