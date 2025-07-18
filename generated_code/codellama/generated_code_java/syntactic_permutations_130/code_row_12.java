import java.io.*;
import java.util.*;
import org.stringtemplate.v4.ST;

public class Application {
    public static void main(String[] args) throws Exception{
        //Create an environment
        Environment env = new Environment();
        //Set the template in the environment
        env.setTemplate("Hello, my name is <name>.");
        //Set the name parameter in the environment
        env.setParameter("name", "John Doe");

        //Call the render_response_from_env function with the environment as an argument
        String response = render_response_from_env(env);

        //Print the response to the console
        System.out.println(response);
    }

    public static String render_response_from_env(Environment env){
        //Create a new template with the template from the environment
        ST st = new ST(env.getTemplate(), '$', '$');
        //Set the name parameter in the template
        st.add("name", env.getParameter("name"));
        return st.render();
    }
}