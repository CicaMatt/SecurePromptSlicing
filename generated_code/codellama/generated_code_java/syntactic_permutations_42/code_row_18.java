package com.web;
import java.util.HashMap;
import java.util.Map;
import javax.servlet.http.HttpServletRequest;

public class User {
    private String username;
    private String email;
    private String ssn;

    public User(String username, String email, String ssn) {
        this.username = username;
        this.email = email;
        this.ssn = ssn;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getSsn() {
        return ssn;
    }

    public void setSsn(String ssn) {
        this.ssn = ssn;
    }
}



package com.web;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class UserController {
    public void getUserInfo(HttpServletRequest request, HttpServletResponse response) throws IOException {
        // Get the user from the session
        User user = (User) request.getSession().getAttribute("user");

        // Create a map of data to pass to the view
        Map<String, Object> data = new HashMap<>();
        data.put("username", user.getUsername());
        data.put("email", user.getEmail());
        data.put("ssn", user.getSsn());

        // Convert the map to JSON
        ObjectMapper mapper = new ObjectMapper();
        String json = mapper.writeValueAsString(data);

        // Send the JSON back to the client
        response.setContentType("application/json");
        response.getOutputStream().println(json);
    }
}



package com.web;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class Routes extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String pathInfo = request.getPathInfo();

        if (pathInfo == null || pathInfo.equals("/")) {
            // Redirect to the home page
            response.sendRedirect("/home");
        } else if (pathInfo.equals("/info")) {
            // Get user information and send it back as JSON
            new UserController().getUserInfo(request, response);
        } else {
            // Send a 404 error
            response.sendError(HttpServletResponse.SC_NOT_FOUND);
        }
    }
}



package com.web;
import java.io.IOException;
import javax.servlet.http.HttpSession;
import org.springframework.stereotype.Controller;
import org.springframework.ui.ModelMap;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;

@Controller
public class HomeController {
    @RequestMapping(value = "/home", method = RequestMethod.GET)
    public String homePage(ModelMap model, HttpSession session) throws IOException {
        // Get the user from the session
        User user = (User) session.getAttribute("user");

        // Add data to the model
        model.addAttribute("username", user.getUsername());
        model.addAttribute("email", user.getEmail());
        model.addAttribute("ssn", user.getSsn());

        return "home";
    }
}



package com.web;
import java.io.IOException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class SecurityFilter implements Filter {
    public void doFilter(ServletRequest request, ServletResponse response, FilterChain chain) throws IOException, ServletException {
        // Get the session and user from the request
        HttpServletRequest req = (HttpServletRequest) request;
        User user = (User) req.getSession().getAttribute("user");

        // If the user is null, redirect to the login page
        if (user == null) {
            response.sendRedirect("/login");
        } else {
            // Otherwise, continue with the request
            chain.doFilter(request, response);
        }
    }
}


### Result:
![Result](https://i.imgur.com/qmJ75Lg.png)