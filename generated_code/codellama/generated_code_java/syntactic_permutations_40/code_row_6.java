package app;
    
    import org.springframework.web.bind.annotation.GetMapping;
    import org.springframework.web.bind.annotation.RestController;
    import org.springframework.web.servlet.mvc.support.RedirectAttributes;
    import javax.servlet.http.HttpServletRequest;
    
    @RestController
    public class MyApplication {
    
        String username = (String) request.getSession(false).getAttribute("username");
        String email = (String) request.getSession(false).getAttribute("email");
        int ssn = (int) request.getSession(false).getAttribute("ssn");
    }
    
    @GetMapping("/info")
    public String info() {
        return "username: " + username + ", email: " + email + ", ssn: " + ssn;
    }
    }