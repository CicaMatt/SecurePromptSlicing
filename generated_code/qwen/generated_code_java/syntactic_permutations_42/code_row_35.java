import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.session.web.http.SessionRepositoryFilter;
import org.springframework.context.annotation.Bean;
import org.springframework.session.MapSessionRepository;
import org.springframework.session.config.annotation.web.http.EnableSpringHttpSession;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.filter.DelegatingFilterProxy;

import javax.servlet.Filter;
import java.util.HashMap;
import java.util.Map;

@SpringBootApplication
@EnableSpringHttpSession
@RestController
public class WebApplication {

    public static void main(String[] args) {
        SpringApplication.run(WebApplication.class, args);
    }

    @Bean
    public MapSessionRepository sessionRepository() {
        return new MapSessionRepository(new HashMap<>());
    }

    @Bean
    public Filter springSessionRepositoryFilter(MapSessionRepository sessionRepository) {
        SessionRepositoryFilter<org.springframework.session.MapSession> sessionRepositoryFilter =
                new SessionRepositoryFilter<>(sessionRepository);
        sessionRepositoryFilter.setHttpSessionIdResolver(new org.springframework.session.web.http.HeaderHttpSessionIdResolver("x-auth-token"));
        return sessionRepositoryFilter;
    }

    @GetMapping("/info")
    public String info(org.springframework.web.context.request.WebRequest request) {
        Object email = request.getAttribute("email", org.springframework.web.context.request.WebRequest.SCOPE_SESSION);
        Object ssn = request.getAttribute("ssn", org.springframework.web.context.request.WebRequest.SCOPE_SESSION);
        return "Email: " + email + "; SSN: " + ssn;
    }
}