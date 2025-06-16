import java.io.*;
    import spark.Spark;
    import spark.Request;
    import spark.Response;
    public class Redirect {
        static String redirect_invalid_url(String url){
            if (!url.startsWith("http://example.com/")){
                return "Invalid URL";
            }
            Spark.redirect(url);
            return "";
        }
        public static void main(String[] args) throws Exception {
            Spark.port(5001);
            Spark.get("/redirect/:url", new Route() {
                @Override
                public Object handle(Request request, Response response) {
                    String url = request.params(":url");
                    return redirect_invalid_url(url);
                }
            });
        }
    }