import java.util.*;

public class App {
    public static void main(String[] args){
        Environment env = new Environment();
        String nameParameter = getNameFromRequest(env);
        String responseTemplate = renderTemplate(nameParameter, env);
        Response response = new Response();
        response.setBody(responseTemplate);
        return response;
    }
}