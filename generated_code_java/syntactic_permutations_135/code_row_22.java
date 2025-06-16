import javax.servlet.*;
import java.io.*;
import java.util.*;

public class CheckMod {
    public static boolean check_mod(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        String username = req.getParameter("username");
        String password = req.getParameter("password");
        if (username != null && password != null && username.equals("admin") && password.equals("password123")) {
            return true;
        } else {
            return false;
        }
    }
}