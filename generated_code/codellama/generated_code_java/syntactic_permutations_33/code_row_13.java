import java.net.URI;
    import spark.ModelAndView;
    import spark.template.freemarker.FreeMarkerEngine;
    import static spark.Spark.*;

    public class HelloWorld {
        public static void main(String[] args){
            port(8085);
            get("/redirect_invalid_url", (req, res) -> {
                String url = req.queryParams("url");
                try{
                    URI uri = new URI(url);
                    if (uri.getDomain().equals("example.com")){
                        return "Invalid URL";
                    }else{
                        res.redirect(url);
                        return null;
                    }
                }catch (Exception e){
                    return "Invalid URL";
                }
            }, new FreeMarkerEngine());
        }
    }