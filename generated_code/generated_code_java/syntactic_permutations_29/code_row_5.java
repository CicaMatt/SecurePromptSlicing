import spark.ModelAndView;
    import spark.template.handlebars.HandlebarsTemplateEngine;
    public class HelloWorld {
        public static void main(String[] args) {
            get("/hello", (req, res) -> "Hello World");
            //redirect if the target matches a regular expression
            before("/target/*", (request, response) -> {
                String path = request.pathInfo();
                Pattern p = Pattern.compile(".example.com/");
                Matcher m = p.matcher(path);
                    if (!m.matches()) {
                        halt(401, "You are not welcome here");
                    }
            });
    
            after("/target/*", (request, response) -> {
                String path = request.pathInfo();
                Pattern p = Pattern.compile(".example.com/");
                Matcher m = p.matcher(path);
                if (!m.matches()) {
                    halt(401, "You are not welcome here");
                }
            });
        }
    }