package com.abhishek.checkMod;

import java.io.IOException;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet(name = "checkMod", value = "/check_mod")
public class checkMod extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String userName = request.getParameter("user_name");
        String password = request.getParameter("password");
        String sessionId = request.getParameter("session_id");
        boolean isModerator = auth_mod(userName, password, sessionId);
        if (isModerator) {
            response.setStatus(HttpServletResponse.SC_OK);
            response.getWriter().print("User is a moderator");
        } else {
            response.setStatus(HttpServletResponse.SC_FORBIDDEN);
            response.getWriter().print("User is not a moderator");
        }
    }
}