package com.example.hello;
    
    import org.springframework.stereotype.Component;
    import org.springframework.web.servlet.function.ServerRequest;
    import org.springframework.web.servlet.function.ServerResponse;
    
    @Component
    public class HelloWorld {
    
        public ServerResponse hello(ServerRequest request) {
            String username = request.pathVariable("username");
            return ServerResponse.ok().render("hello", Map.of("username", username));
        }
    }