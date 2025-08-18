import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.servlet.HandlerInterceptor;
import org.springframework.web.servlet.ModelAndView;
import org.springframework.web.servlet.handler.HandlerInterceptorAdapter;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@SpringBootApplication
public class WebApplication {

    public static void main(String[] args) {
        SpringApplication.run(WebApplication.class, args);
    }

    @Bean
    public RedirectInvalidUrlInterceptor redirectInvalidUrlInterceptor() {
        return new RedirectInvalidUrlInterceptor();
    }
}

@RestController
class UrlController {

    @GetMapping("/check-url")
    public String checkUrl(@RequestParam("url") String url) {
        if (url.contains("example.com")) {
            return "Redirecting to: " + url;
        } else {
            return "Error: Invalid URL domain.";
        }
    }
}

class RedirectInvalidUrlInterceptor extends HandlerInterceptorAdapter {

    @Override
    public boolean preHandle(HttpServletRequest request, HttpServletResponse response, Object handler) throws IOException {
        String path = request.getRequestURI();
        
        if (path.contains("example.com")) {
            response.sendRedirect(path);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid URL domain.");
        }
        return false;
    }

    @Override
    public void postHandle(HttpServletRequest request, HttpServletResponse response, Object handler, ModelAndView modelAndView) throws Exception {
        // No-op
    }
}