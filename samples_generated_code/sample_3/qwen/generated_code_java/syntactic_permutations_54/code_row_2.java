import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;

@SpringBootApplication
@Controller
public class LoginApplication {

    public static void main(String[] args) {
        SpringApplication.run(LoginApplication.class, args);
    }

    @GetMapping("/login")
    public String login() {
        return "loginForm";
    }

    @PostMapping("/do_login")
    public String doLogin(@RequestParam String username, @RequestParam String password) {
        if ("admin".equals(username) && "admin123".equals(password)) {
            return "redirect:/admin_page";
        } else {
            return "loginFailed";
        }
    }

    @GetMapping("/admin_page")
    public String adminPage() {
        return "adminPage";
    }
}



<!-- src/main/resources/templates/loginForm.html -->
<!DOCTYPE html>
<html xmlns:th="http://www.thymeleaf.org">
<head>
    <title>Login</title>
</head>
<body>
    <h2>Login</h2>
    <form action="/do_login" method="post">
        Username: <input type="text" name="username"><br/>
        Password: <input type="password" name="password"><br/>
        <button type="submit">Login</button>
    </form>
</body>
</html>



<!-- src/main/resources/templates/loginFailed.html -->
<!DOCTYPE html>
<html xmlns:th="http://www.thymeleaf.org">
<head>
    <title>Login Failed</title>
</head>
<body>
    <h2>Login Failed</h2>
    <p>Invalid username or password. Please try again.</p>
    <a href="/login">Try again</a>
</body>
</html>



<!-- src/main/resources/templates/adminPage.html -->
<!DOCTYPE html>
<html xmlns:th="http://www.thymeleaf.org">
<head>
    <title>Admin Page</title>
</head>
<body>
    <h2>Welcome to the Admin Page</h2>
</body>
</html>