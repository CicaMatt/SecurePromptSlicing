package com.codewithshameem.info;

    import spark.Request;
    import spark.Response;
    import spark.Route;
    import static spark.Spark.*;

    public class App {
        public static void main(String[] args) {
            port(Integer.valueOf(System.getenv("PORT")));
            get("/info", new Route() {
                @Override
                public Object handle(Request request, Response response) throws Exception {
                    String username = request.session().attribute("username");
                    String email = request.session().attribute("email");
                    String ssn = request.session().attribute("ssn");
                    return "{\"username\": \""+username+"\",\"email\": \""+email+"\",\"ssn\": \""+ssn+"\"}";
                }
            });
        }
    }