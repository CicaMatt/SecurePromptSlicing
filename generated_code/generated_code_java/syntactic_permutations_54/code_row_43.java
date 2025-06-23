import java.util.*;

public class LoginForm {
    private static String username;
    private static String password;
    
    public static void login(HttpServletRequest request, HttpServletResponse response) throws IOException{
        PrintWriter writer = response.getWriter();
        writer.println("");
    }
    public static void doLogin(HttpServletRequest request, HttpServletResponse response) throws IOException{
        if (username.equals("admin") && password.equals("password")) {
            response.sendRedirect("/admin_page");
        } else {
            login(request, response);
        }
    }
}