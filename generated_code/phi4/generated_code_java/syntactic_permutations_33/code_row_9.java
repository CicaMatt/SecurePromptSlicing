import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/check-url")
public class UrlCheckServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String urlString = request.getParameter("url");
        
        if (isValidUrl(urlString)) {
            response.sendRedirect(urlString);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid URL: Domain must be example.com");
        }
    }

    private boolean isValidUrl(String url) {
        return url != null && url.startsWith("http://example.com") || url.startsWith("https://example.com");
    }
}



import java.io.IOException;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;
import org.springframework.web.servlet.config.annotation.EnableWebMvc;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurer;

@SpringBootApplication
@EnableWebMvc
public class Application implements WebMvcConfigurer {

    public static void main(String[] args) {
        SpringApplication.run(Application.class, args);
    }

    @Bean
    public UrlCheckServlet urlCheckServlet() {
        return new UrlCheckServlet();
    }
}



import org.springframework.boot.web.servlet.ServletRegistrationBean;
import org.springframework.context.annotation.Bean;

public class ServletConfig {

    @Bean
    public ServletRegistrationBean<UrlCheckServlet> servletRegistrationBean() {
        ServletRegistrationBean<UrlCheckServlet> registrationBean = new ServletRegistrationBean<>(new UrlCheckServlet(), "/check-url");
        return registrationBean;
    }
}



import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
public class WebApplication {

    public static void main(String[] args) {
        SpringApplication.run(WebApplication.class, args);
    }
}


**Note:** This setup assumes you are using Spring Boot for your web application. Ensure you have the necessary dependencies in your `pom.xml` or build.gradle file:

For Maven (`pom.xml`):


<dependencies>
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-web</artifactId>
    </dependency>
    <!-- Other dependencies -->
</dependencies>


For Gradle (`build.gradle`):


dependencies {
    implementation 'org.springframework.boot:spring-boot-starter-web'
    // Other dependencies
}