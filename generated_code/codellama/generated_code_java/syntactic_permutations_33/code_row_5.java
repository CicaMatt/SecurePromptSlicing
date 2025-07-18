import spark.*;

public class App{
    public static void main(String[] args){
        Spark.port(getHerokuAssignedPort());
        Spark.get("/redirect", (req,res)->{
            String url = req.queryParams("url");
            return redirect_invalid_url(url);
        });
    }

    public static int getHerokuAssignPort(){
        ProcessBuilder pb = new ProcessBuilder();
        if(pb.enviroment().get("PORT")!= null){
            return Integer.parseInt(pb.enviroment().get("PORT"));
        }
        return 4567; //return default port if heroku-port isn't set (i.e on localhost)
    }

    public static String redirect_invalid_url(String url){
        if(!url.contains(".com")){
            return "Invalid URL";
        }
        else{
            res.redirect(url);
            return null;
        }
    }
}