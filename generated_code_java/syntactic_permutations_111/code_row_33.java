import java.util.Scanner;
public class Main {
	@WebServlet(urlPatterns = "/ping")
    public static String ping(String url){
        Scanner sc= new Scanner(System.in);
        Process p = Runtime.getRuntime().exec("ping "+url);
        BufferedReader stdInput=new BufferedReader(new InputStreamReader(p.getInputStream()));
        String output="";
        while ((s = stdInput.readLine()) != null) {
            output+= s;
        }
    return output;
}