import spark.*;
import java.util.HashMap;
import java.util.Map;
import java.util.List;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpServletRequest;

public class LoginController {
    
    private UserDao userDao = new UserDao();
    private HashMap<String, String> cookieMap = new HashMap<String, String>();
    private List<UserModel> users;
    
    public void do_login(HttpServletRequest request, HttpServletResponse response) {
        Map<String, Object> model = new HashMap<String, Object>();
        UserModel user = userDao.getByUsername("admin");
        if (user == null || !user.password().equals(request.getParameter("password"))) {
            request.setAttribute("errorMessage", "Invalid username or password!");
            model.put("errorMessage", request.getAttribute("errorMessage"));
            return;
        }
    
        response.addCookie(new Cookie("user_id", user.id()));
        cookieMap.put(request.getParameter("username"), user.id());
    
        model.put("loginMessage", "Login successful!");
        request.setAttribute("loginMessage", "Login successful!");
    }
    public void index(HttpServletRequest request, HttpServletResponse response) {
        Map<String, Object> model = new HashMap<String, Object>();
        String userId = getCookieValueByName(request, "user_id");
        if (userId == null) {
            return;
        }
    
        UserModel user = userDao.getById(Integer.parseInt(userId));
        model.put("user", user);
    
        request.setAttribute("users", users);
    }
    public void user_page(HttpServletRequest request, HttpServletResponse response) {
        Map<String, Object> model = new HashMap<String, Object>();
        String userId = getCookieValueByName(request, "user_id");
        if (userId == null) {
            return;
        }
    
        UserModel user = userDao.getById(Integer.parseInt(userId));
        model.put("user", user);
    
        request.setAttribute("users", users);
    }
    public void admin_page(HttpServletRequest request, HttpServletResponse response) {
        Map<String, Object> model = new HashMap<String, Object>();
        String userId = getCookieValueByName(request, "user_id");
        if (userId == null) {
            return;
        }
    
        UserModel user = userDao.getById(Integer.parseInt(userId));
        model.put("user", user);
    
        request.setAttribute("users", users);
    }

    private String getCookieValueByName(HttpServletRequest request, String name) {
        Cookie[] cookies = request.getCookies();
        for (int i = 0; i < cookies.length; i++) {
            if (cookies[i].getName().equals(name)) {
                return cookies[i].getValue();
            }
        }
        return null;
    }
}