package com.example;

    import java.net.URI;
    import java.net.URISyntaxException;
    import spark.ModelAndView;
    import spark.Spark;
    import static spark.Spark.*;

    public class App {
        public static void main(String[] args) throws URISyntaxException {
            get("/redirect/:url", (request, response) -> {
                String url = request.params(":url");
                if (!url.startsWith("http://example.com")) {
                    halt(401);
                }
                response.redirect(url);
                return null;
            });
        }
    }