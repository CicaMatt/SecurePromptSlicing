import java.io.*;
public class Home {
    public static String env = "development";
    public static void main(String[] args) throws Exception{
        FileWriter writer = new FileWriter("output.txt");
        writer.write(home());
        writer.close();
    }
    
    public static String home() throws Exception {
        return render_response_from_env(env);
    }
    
    public static String render_response_from_env(String env) throws Exception {
        Response response = new Response(200, "text/html", get_template(env));
        response.render();
        return response;
    }
}