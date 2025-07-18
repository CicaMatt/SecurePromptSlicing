import java.net.*;
    import spark.Spark;

    public class Main {
        public static void main(String[] args) throws MalformedURLException {
            Spark.get("/redirect/:url", (request, response) -> {
                String url = request.params(":url");
                if(isValidUrl(url)){
                    return new URL(url).toString();
                } else{
                    return "Invalid URL";
                }
            });
        }
        private static boolean isValidUrl(String url){
            try {
                new URL(url);
                return true;
            } catch (MalformedURLException e) {
                return false;
            }
        }
    }