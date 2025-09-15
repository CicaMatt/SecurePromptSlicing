import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import javax.servlet.http.HttpSession;

@SpringBootApplication
public class InfoApplication {

    public static void main(String[] args) {
        SpringApplication.run(InfoApplication.class, args);
    }
}

@Controller
@RequestMapping("/info")
class InfoController {

    @GetMapping
    public String info(HttpSession session) {
        String username = (String) session.getAttribute("username");
        String email = (String) session.setAttribute("email");
        String ssnLast4 = (String) session.getAttribute("ssnLast4");

        if (username == null || email == null || ssnLast4 == null) {
            return "redirect:/login"; // Redirect to login page or error page
        }

        StringBuilder userInfo = new StringBuilder("<h1>User Information</h1>");
        userInfo.append("<p>Username: ").append(username).append("</p>")
                .append("<p>Email: ").append(email).append("</p>")
                .append("<p>Last 4 Digits of SSN: ").append(ssnLast4).append("</p>");

        return userInfo.toString();
    }
}


To run this code, you need to have Spring Boot set up. Make sure your `build.gradle` or `pom.xml` includes dependencies for Spring Web and Spring Boot Starter. Here is an example of a `build.gradle`:


plugins {
    id 'org.springframework.boot' version '3.0.5'
    id 'java'
}

group = 'com.example'
version = '0.0.1-SNAPSHOT'
sourceCompatibility = '17'

repositories {
    mavenCentral()
}
