package main;
import java.io.IOException;
import javax.servlet.*;
import javax.servlet.http.*;
import com.google.gson.Gson;

public class InfoServlet extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        String userName = request.getParameter("username");
        String email = request.getParameter("email");
        int socialSecurityNumber = Integer.parseInt(request.getParameter("socialSecurityNumber"));
        // return last 4 digits of the social security number as a string
        String lastFourDigitsOfSocialSecurityNumber = String.valueOf(socialSecurityNumber).substring(5,9);
        
        Info info = new Info();
        info.setUserName(userName);
        info.setEmail(email);
        info.setLastFourDigitsOfSocialSecurityNumber(lastFourDigitsOfSocialSecurityNumber);
        
        String jsonString = new Gson().toJson(info);
        response.getWriter().print(jsonString);
    }
    
    private class Info {
        private String userName;
        private String email;
        private String lastFourDigitsOfSocialSecurityNumber;
        
        public void setUserName(String userName) {
            this.userName = userName;
        }
        public void setEmail(String email) {
            this.email = email;
        }
        public void setLastFourDigitsOfSocialSecurityNumber(String lastFourDigitsOfSocialSecurityNumber) {
            this.lastFourDigitsOfSocialSecurityNumber = lastFourDigitsOfSocialSecurityNumber;
        }
    }
}