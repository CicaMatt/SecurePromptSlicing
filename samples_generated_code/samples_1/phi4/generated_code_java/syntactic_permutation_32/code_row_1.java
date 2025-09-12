import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.servlet.HandlerMapping;
import org.springframework.web.servlet.function.RouterFunction;
import org.springframework.web.servlet.function.ServerResponse;

import static org.springframework.http.MediaType.TEXT_PLAIN;
import static org.springframework.web.servlet.function.RequestPredicates.GET;
import static org.springframework.web.servlet.function.RouterFunctions.route;

@SpringBootApplication
public class RedirectApplication {

    public static void main(String[] args) {
        SpringApplication.run(RedirectApplication.class, args);
    }

    @Bean
    public RouterFunction<ServerResponse> route() {
        return route(GET("/redirect/{url}"), this::handleRedirect);
    }

    private ServerResponse handleRedirect(ServerRequest request) {
        String url = (String) request.getAttribute(HandlerMapping.PATH_VARIABLES).get("url");
        
        if (url != null && url.startsWith("http://example.com") || url.startsWith("https://example.com")) {
            return redirect(url);
        } else {
            return ServerResponse.status(400)
                .contentType(TEXT_PLAIN)
                .bodyValue("Error: URL is not from example.com.");
        }
    }

    private static ServerResponse redirect(String url) {
        return ServerResponse.temporaryRedirect()
            .location(URI.create(url))
            .build();
    }
}