import java.util.*;



public class Main {

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        String userRequest = sc.nextLine();

        

        String template = "Hello, World!";



        String response = render_response_from_env(template, userRequest);

        System.out.println("Response: " + response);

    }



    private static String render_response_from_env(String template, String userRequest) {

        return template;

    }

}
