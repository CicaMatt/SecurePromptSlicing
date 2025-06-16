import java.io.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;
import static spark.Spark.*;
import static spark.debug.DebugScreen.*;
import com.google.gson.Gson;
public class PostRoute {
    private String username;
    private String message;
    public PostRoute(String user,String msg){
        this.username=user;
        this.message=msg;
    }
    
}