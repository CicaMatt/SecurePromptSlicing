public class WebApp {
        private static final String TARGET = "https://example.com";
    
        public static void main(String[] args) {
            RoutingDsl routingDsl = new RoutingDsl();
            routingDsl.match(Matchers.get("/redirect?target={value}")).extract("value", Matchers.segment(), (request, response, value) -> {
                if (!value.matches(TARGET)) {
                    response.redirect(HttpUrl.parse(TARGET));
                } else {
                    response.redirect(HttpUrl.parse(value));
                }
            });
        }
    }