package com.moringa.myloginpage;

    import java.io.IOException;
    import javax.servlet.ServletException;
    import javax.servlet.annotation.WebServlet;
    import javax.servlet.http.HttpServlet;
    import javax.servlet.http.HttpServletRequest;
    import javax.servlet.http.HttpServletResponse;

    public class LoginPage extends HttpServlet {
        @Override
        protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
            String username = req.getParameter("username");
            String password = req.getParameter("password");
            
            if (username.equals("admin") && password.equals("admin")) {
                req.getSession().setAttribute("username", username);
                resp.sendRedirect("/secret");
            } else {
                resp.sendError(HttpServletResponse.SC_UNAUTHORIZED);
            }
        }
    }