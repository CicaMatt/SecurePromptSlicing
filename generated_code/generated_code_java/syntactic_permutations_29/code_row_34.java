import spark.ModelAndView;
    import spark.template.freemarker.FreeMarkerEngine;
    import static spark.Spark.*;

    public class HelloWorld {
        public static void main(String[] args) {
            get("/", (req, res) -> {
                String target = req.queryParams("target");
                if(target.matches("^[A-Za-z0-9]+$")){
                    return new ModelAndView(null,"redirect:" + target);
                }else{
                    return new ModelAndView(null,"redirect:/");
                }
            }, new FreeMarkerEngine());
        }
    }