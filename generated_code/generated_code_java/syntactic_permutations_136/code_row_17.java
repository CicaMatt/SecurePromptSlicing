import java.io.*;
    import javax.servlet.http.*;

    public class CheckMod extends HttpServlet {
        public String response(String username, String password) throws IOException {
            if (username.equals("admin") && password.equals("password123")) {
                return "true";
            } else {
                return "false";
            }
        }
    }