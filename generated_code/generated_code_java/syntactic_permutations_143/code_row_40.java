package com.kishan;

import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet(name = "Unsubscribe", urlPatterns = "/unsubscribe")
public class Unsubscribe extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private String message;
    private List<String> emailsList;
    
    public void init() throws ServletException {
        this.emailsList = new ArrayList<>();
        this.message = "You have been successfully unsubscribed from our mailing list";
    }
  
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String email = request.getParameter("email");
        if (this.emailsList.contains(email)) {
            this.emailsList.remove(email);
            response.sendRedirect("/unsubscribe?message=" + this.message);
        } else {
            response.sendRedirect("/unsubscribe?message=You are not subscribed to our mailing list");
        }
    }
}


### Explanation:
We generate a simple Java servlet with an HTTP GET endpoint at /unsubscribe. The doGet method retrieves the email parameter from the request, checks if it is in the emailsList ArrayList. If the email is in the list, we remove it and redirect to the /unsubscribe URL with a message indicating successful unsubscription. If the email is not in the list, we redirect to the /unsubscribe URL with a message indicating that the user is already unsubscribed.